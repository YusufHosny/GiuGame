#include "penemyobject.h"
#include "collidercomponent.h"
#include "animationcomponent.h"

PEnemyObject::PEnemyObject(std::unique_ptr<PEnemy> pEnemyModel): pEnemyModel(std::move(pEnemyModel)), TileObject("PEnemy") {}

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

    this->components.emplace_back(new AnimationComponent);
    this->getComponent<AnimationComponent>()->setUpdateTime(200);
    this->getComponent<AnimationComponent>()->setAnimation(PEnemyObject::LEFT,
                                                           this->AnimationFrameCounts[PEnemyObject::LEFT]);
}

const Tile& PEnemyObject::getTile() const {
    return *this->pEnemyModel;
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

const PEnemy &PEnemyObject::getPEnemy() const
{
    return *this->pEnemyModel;
}
