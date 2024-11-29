#include "playerobject.h"
#include "collidercomponent.h"

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

}

void PlayerObject::step(qint64 deltaT, std::set<GameInput> inputs)
{
    // TODO
}


void PlayerObject::onCollision(std::shared_ptr<GameObject> other)
{
    // TODO
}


std::string PlayerObject::dumpData() const
{
    return ""; // TODO
}
