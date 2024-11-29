#include "collidercomponent.h"

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
