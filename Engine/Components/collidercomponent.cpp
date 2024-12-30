#include "collidercomponent.h"

ColliderComponent::ColliderComponent(std::function<void(std::shared_ptr<GameObject>)> onCollision, std::function<std::array<int, 2>()> getPosition):
        onCollision(onCollision), getPositionImpl(getPosition) {};

void ColliderComponent::notifyCollision(std::shared_ptr<GameObject> other)
{
    this->onCollision(other);
}

std::array<int, 2> ColliderComponent::getPosition()
{
    return this->getPositionImpl();
}

void ColliderComponent::step_component(GameObject &owner)
{

}
