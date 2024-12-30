#include "playerobject.h"
#include "collidercomponent.h"
#include "enemyobject.h"
#include "penemyobject.h"
#include "healthpackobject.h"
#include "levelobject.h"
#include "giugameconfig.h"

PlayerObject::PlayerObject(std::unique_ptr<Protagonist> playerModel): playerModel(std::move(playerModel)), GameObject("Player") {}

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

    this->moveCooldownLeft = 0;
    this->poisonCooldownLeft = 0;
}

void PlayerObject::step(qint64 deltaT, std::set<GameInput> inputs)
{
    if(this->moveCooldownLeft > 0) {
        this->moveCooldownLeft -= deltaT;
        std::cout << this->moveCooldownLeft << "ms left, " << deltaT << "ms delta" << std::endl;
    }
    this->stepPoison(deltaT);

    for(auto &input: inputs) {
        if(input.type == GameInputType::PLAYERMOVE) {
            this->move(deltaT, input.parameter);
        }
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

void PlayerObject::move(qint64 deltaT, int dir) { // TODO CHECK MOVE VALID
    if(this->moveCooldownLeft > 0) return;

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


void PlayerObject::onCollision(std::shared_ptr<GameObject> other)
{
    if(auto e = std::dynamic_pointer_cast<EnemyObject>(other)) {
        this->onCollision(e);
    }
    else if(auto pe = std::dynamic_pointer_cast<PEnemyObject>(other)) {
        this->onCollision(pe);
    }
    else if(auto hp = std::dynamic_pointer_cast<HealthPackObject>(other)) {
        this->onCollision(hp);
    }
}

void PlayerObject::onCollision(std::shared_ptr<EnemyObject> e) {
    float health = this->playerModel->getHealth();
    float eHealth = e->getEnemy().getValue();

    this->playerModel->setHealth(health - eHealth);

    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(this->parent);
    lo->removeChild(e);
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


std::string PlayerObject::dumpData() const
{
    return ""; // TODO
}
