#include "benemyobject.h"
#include "collidercomponent.h"
#include "animationcomponent.h"
#include "giugameconfig.h"

BEnemyObject::BEnemyObject(std::unique_ptr<Enemy> enemyModel): enemyModel(std::move(enemyModel)), TileObject("BEnemy") {}

void BEnemyObject::init()
{
    this->components.emplace_back(new ColliderComponent(
        [this](std::shared_ptr<GameObject> other) {
            this->onCollision(other);
        },
        [this]() {
            // getPosition
            std::array<int, 2> out {this->enemyModel->getXPos(), this->enemyModel->getYPos()};
            return out;
        }
        ));

    this->blinkTime = GiuGameConfig::getInstance().blinkCooldown; // can be adjusted or random
    this->blinkTimeLeft = this->blinkTime;
    this->blinkVisible = false;

    this->components.emplace_back(new AnimationComponent);
    this->getComponent<AnimationComponent>()->setUpdateTime(this->blinkTime / this->AnimationFrameCounts[BEnemyObject::BLINK]);
    this->getComponent<AnimationComponent>()->setAnimation(BEnemyObject::IDLE,
                                                           this->AnimationFrameCounts[BEnemyObject::IDLE]);


}

const Tile& BEnemyObject::getTile() const {
    return *this->enemyModel;
}

void BEnemyObject::step(qint64 deltaT, std::set<GameInput> inputs)
{
    if(this->blinkTimeLeft > 0) {
        this->blinkTimeLeft -= deltaT;
    }
    else {
        this->blinkVisible = !this->blinkVisible;
        unsigned int state = this->blinkVisible ? BEnemyObject::BLINK : BEnemyObject::IDLE;
        this->getComponent<AnimationComponent>()->setAnimation(state,
                                                               this->AnimationFrameCounts[state]);


        std::shared_ptr<ColliderComponent> collider = this->getComponent<ColliderComponent>(); // activate collisions only when visible
        collider->setActive(this->blinkVisible);

        this->blinkTimeLeft = this->blinkTime;
    }
}

void BEnemyObject::onCollision(std::shared_ptr<GameObject> other) {

}


std::string BEnemyObject::dumpData() const
{
    return ""; // TODO
}
