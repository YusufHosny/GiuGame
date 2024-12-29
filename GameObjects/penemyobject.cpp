#include "penemyobject.h"
#include "collidercomponent.h"

PEnemyObject::PEnemyObject(std::unique_ptr<PEnemy> pEnemyModel): pEnemyModel(std::move(pEnemyModel)), GameObject("PEnemy") {}

void PEnemyObject::init()
{
    this->components.emplace_back(new ColliderComponent(
        [this](std::shared_ptr<GameObject> other) {
            this->onCollision(other);
        },
        [this]() {
            // getPosition
            std::array<int, 2> out {this->pEnemyModel->getXPos(), this->pEnemyModel->getYPos()};
            return out;
        }
        ));
}

void PEnemyObject::step(qint64 deltaT, std::set<GameInput> inputs)
{

}

void PEnemyObject::onCollision(std::shared_ptr<GameObject> other) {

}


std::string PEnemyObject::dumpData() const
{
    return ""; // TODO
}
