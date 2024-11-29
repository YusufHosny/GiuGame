#include "healthpackobject.h"
#include "collidercomponent.h"

HealthPackObject::HealthPackObject(std::unique_ptr<Tile> tile): tile(std::move(tile)), GameObject("Health Pack") {}

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
