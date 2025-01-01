#include "enemyobject.h"
#include "collidercomponent.h"

EnemyObject::EnemyObject(std::unique_ptr<Enemy> enemyModel): enemyModel(std::move(enemyModel)), TileObject("Enemy") {}

void EnemyObject::init()
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
}

const Tile& EnemyObject::getTile() const {
    return *this->enemyModel;
}

void EnemyObject::step(qint64 deltaT, std::set<GameInput> inputs)
{

}

void EnemyObject::onCollision(std::shared_ptr<GameObject> other) {

}


std::string EnemyObject::dumpData() const
{
    return ""; // TODO
}
