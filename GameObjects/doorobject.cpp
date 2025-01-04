#include "doorobject.h"
#include "collidercomponent.h"
#include "animationcomponent.h"

DoorObject::DoorObject(QString targetLevel, int x, int y) : target(targetLevel), TileObject("Door"), t(x, y, 0) {}


void DoorObject::init()
{
    this->components.emplace_back(new ColliderComponent(
        [this](std::shared_ptr<GameObject> other) {

        },
        [this]() {
            // getPosition
            std::array<int, 2> out {this->getTile().getXPos(), this->getTile().getYPos()};
            return out;
        }
        ));


    this->components.emplace_back(new AnimationComponent);
    this->getComponent<AnimationComponent>()->setUpdateTime(20);
    this->getComponent<AnimationComponent>()->setAnimation(DoorObject::IDLE,
                                                           this->AnimationFrameCounts[DoorObject::IDLE]);

}

QString DoorObject::getTarget() const {
    return this->target;
}

const Tile& DoorObject::getTile() const {
    return this->t;
};


std::string DoorObject::dumpData() const
{
    return ""; // TODO
}
