#include "benemyobject.h"
#include "collidercomponent.h"
#include "giugameconfig.h"

BEnemyObject::BEnemyObject(std::unique_ptr<Enemy> enemyModel): enemyModel(std::move(enemyModel)), GameObject("BEnemy") {}

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
}

void BEnemyObject::step(qint64 deltaT, std::set<GameInput> inputs)
{

}

void BEnemyObject::onCollision(std::shared_ptr<GameObject> other) {

}


std::string BEnemyObject::dumpData() const
{
    return ""; // TODO
}
