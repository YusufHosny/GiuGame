#include "playerobject.h"

#include "enemyobject.h"
#include "penemyobject.h"
#include "benemyobject.h"
#include "healthpackobject.h"
#include "levelobject.h"
#include "doorobject.h"
#include "giugameobject.h"

#include "giugameconfig.h"

#include "pathtracercomponent.h"
#include "collidercomponent.h"
#include "autoplaycomponent.h"
#include "animationcomponent.h"

PlayerObject::PlayerObject(std::unique_ptr<Protagonist> playerModel): playerModel(std::move(playerModel)), TileObject("Player") {}

void PlayerObject::init()
{
    this->components.emplace_back(new ColliderComponent(
        [this](std::shared_ptr<GameObject> other) {
            this->onCollision(other);
        },
        [this]() {
            // getPosition
            std::array<int, 2> out {this->playerModel->getXPos(), this->playerModel->getYPos()};
            return out;
        }
    ));

    this->components.emplace_back(new AutoPlayComponent());
    this->getComponent<AutoPlayComponent>()->setActive(false);

    this->components.emplace_back(new PathTracerComponent());
    this->getComponent<PathTracerComponent>()->setCurrent(this->getTile());

    this->components.emplace_back(new AnimationComponent);
    this->getComponent<AnimationComponent>()->setUpdateTime(150);
    this->facing = Direction::DOWN;
    this->state = PlayerObject::IDLEUP;
    this->getComponent<AnimationComponent>()->setAnimation(PlayerObject::IDLEUP + static_cast<int>(facing),
                                                           this->AnimationFrameCounts[PlayerObject::IDLEUP + static_cast<int>(facing)]);

    this->moveCooldownLeft = 0;
    this->poisonCooldownLeft = 0;

}

void PlayerObject::step(qint64 deltaT, std::set<GameInput> inputs)
{
    if(this->moveCooldownLeft > 0) {
        this->setState(PlayerObject::WALKUP);
        this->moveCooldownLeft -= deltaT;
    }
    else {
        this->setState(PlayerObject::IDLEUP);
    }

    this->stepPoison(deltaT);

    for(auto &input: inputs) {
        if(input.type == GameInputType::PLAYERMOVE) {
            this->facing = static_cast<Direction>(input.parameter);
            this->move(input.parameter);
        }
        else if(input.type == GameInputType::AUTOPLAY) {
            this->getComponent<AutoPlayComponent>()->reset();
            this->getComponent<AutoPlayComponent>()->toggle();
        }
        else if(input.type == GameInputType::GOTO) {
            this->getComponent<AutoPlayComponent>()->reset();
            this->getComponent<AutoPlayComponent>()->setTarget(std::dynamic_pointer_cast<LevelObject>(this->parent)->getTiles().at(input.parameter).get());
            this->getComponent<AutoPlayComponent>()->setOnce(true);
            this->getComponent<AutoPlayComponent>()->setActive(true);
        }
    }

}

void PlayerObject::setState(unsigned int state) {
    if(this->state != state) {
        this->state = state;
        this->updateAnimation(); // only update on state change
    }
    else {
        this->state = state;
    }
}

void PlayerObject::updateAnimation() {
    if(this->state == PlayerObject::DYING) {
        this->getComponent<AnimationComponent>()->setAnimation(PlayerObject::DYING, this->AnimationFrameCounts[PlayerObject::DYING]);
        this->getComponent<AnimationComponent>()->setOnce(true);
    }
    else if(this->state == PlayerObject::FIGHTING) {
        this->getComponent<AnimationComponent>()->setAnimation(PlayerObject::FIGHTING, this->AnimationFrameCounts[PlayerObject::FIGHTING]);
        this->getComponent<AnimationComponent>()->setOnce(true);
    }
    else if(this->state == PlayerObject::WALKUP) {
        this->getComponent<AnimationComponent>()->setAnimation(PlayerObject::WALKUP + static_cast<int>(facing),
                                                    this->AnimationFrameCounts[PlayerObject::WALKUP + static_cast<int>(facing)]);
    }
    else {
        this->getComponent<AnimationComponent>()->setAnimation(PlayerObject::IDLEUP + static_cast<int>(facing),
                                                    this->AnimationFrameCounts[PlayerObject::IDLEUP + static_cast<int>(facing)]);
    }
}

void PlayerObject::stepPoison(qint64 deltaT) {
    if(this->poisonCooldownLeft > 0) {
        this->poisonCooldownLeft -= deltaT;
    } else if(this->poisonAmount > 0) {
        this->playerModel->setHealth(this->playerModel->getHealth() - 10);
        this->poisonAmount -= 10;
        this->poisonCooldownLeft = GiuGameConfig::getInstance().poisonCooldown;
    }
}

void PlayerObject::move(int dir) { // TODO CHECK MOVE VALID
    if(this->moveCooldownLeft > 0) {
        return;
    }

    int x = this->playerModel->getXPos(), y = this->playerModel->getYPos();

    switch(dir) {
        case(Direction::UP):
            y -= 1;
            break;

        case(Direction::DOWN):
            y += 1;
            break;

        case(Direction::LEFT):
            x -= 1;
            break;

        case(Direction::RIGHT):
            x += 1;
            break;
    }

    // get energy needed for target tile
    float energy = this->playerModel->getEnergy();
    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(this->parent);
    float targetValue = lo->getTile(x, y)->getValue();

    // block movement for inf tiles
    if(!std::isinf(targetValue)) {
        this->playerModel->setPos(x, y);
        this->playerModel->setEnergy(energy - targetValue);
        this->moveCooldownLeft = GiuGameConfig::getInstance().movementCooldown;
    }
}

void PlayerObject::setShowPath(bool showPath)
{
    this->showPath = showPath;
}

bool PlayerObject::isShowPath() const
{
    return this->showPath;
}

float PlayerObject::getPoisonAmount() const
{
    return this->poisonAmount;
}

const Tile& PlayerObject::getTile() const {
    return *this->playerModel;
}


void PlayerObject::onCollision(std::shared_ptr<GameObject> other)
{
    this->setState(PlayerObject::FIGHTING);
    if(auto e = std::dynamic_pointer_cast<EnemyObject>(other)) {
        this->onCollision(e);
    }
    else if(auto be = std::dynamic_pointer_cast<BEnemyObject>(other)) {
        this->onCollision(be);
    }
    else if(auto pe = std::dynamic_pointer_cast<PEnemyObject>(other)) {
        this->onCollision(pe);
    }
    else if(auto hp = std::dynamic_pointer_cast<HealthPackObject>(other)) {
        this->onCollision(hp);
    }
    else if(auto d = std::dynamic_pointer_cast<DoorObject>(other)) {
        this->onCollision(d);
    }
}

void PlayerObject::onCollision(std::shared_ptr<EnemyObject> e) {
    float health = this->playerModel->getHealth();
    float eHealth = e->getEnemy().getValue();

    this->playerModel->setHealth(health - eHealth);

    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(this->parent);
    lo->removeChild(e);
}

void PlayerObject::onCollision(std::shared_ptr<BEnemyObject> be) {
    float health = this->playerModel->getHealth();
    float eHealth = be->getEnemy().getValue();

    this->playerModel->setHealth(health - eHealth);

    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(this->parent);
    lo->removeChild(be);
}


void PlayerObject::onCollision(std::shared_ptr<PEnemyObject> pe) {
    float health = this->playerModel->getHealth();
    float eHealth = pe->getPEnemy().getValue();

    this->poisonAmount = pe->getPEnemy().getPoisonLevel();
    this->poisonCooldownLeft = GiuGameConfig::getInstance().poisonCooldown;

    this->playerModel->setHealth(health - eHealth);

    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(this->parent);
    lo->removeChild(pe);
}

void PlayerObject::onCollision(std::shared_ptr<HealthPackObject> hp) {
    float health = this->playerModel->getHealth();
    this->playerModel->setHealth(health + hp->getHP().getValue());

    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(this->parent);
    lo->removeChild(hp);
}

void PlayerObject::onCollision(std::shared_ptr<DoorObject> d) {
    std::dynamic_pointer_cast<GiuGameObject>(this->parent->getParent())->nextLevel(d->getTarget());
}

const Protagonist &PlayerObject::getProtagonist() const
{
    return *this->playerModel;
}


std::string PlayerObject::dumpData() const
{
    return ""; // TODO
}

