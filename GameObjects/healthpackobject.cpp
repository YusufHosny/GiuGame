#include "healthpackobject.h"
#include "collidercomponent.h"
#include "animationcomponent.h"

HealthPackObject::HealthPackObject(std::unique_ptr<Tile> tile): tile(std::move(tile)), TileObject("Health Pack") {}

void HealthPackObject::init()
{
    this->components.emplace_back(new ColliderComponent(
        [this](std::shared_ptr<GameObject> other) {
            this->onCollision(other);
        },
        [this]() {
            // getPosition
            std::array<int, 2> out {this->tile->getXPos(), this->tile->getYPos()};
            return out;
        }
    ));

    this->components.emplace_back(new AnimationComponent);
    this->getComponent<AnimationComponent>()->setUpdateTime(200);
    this->getComponent<AnimationComponent>()->setAnimation(HealthPackObject::IDLE,
                                                           this->AnimationFrameCounts[HealthPackObject::IDLE]);

}

const Tile& HealthPackObject::getTile() const {
    return *this->tile;
}

void HealthPackObject::step(qint64 deltaT, std::set<GameInput> inputs)
{
    // TODO
}


void HealthPackObject::onCollision(std::shared_ptr<GameObject> other)
{
    // TODO
}


std::string HealthPackObject::dumpData() const
{
    return ""; // TODO
}
