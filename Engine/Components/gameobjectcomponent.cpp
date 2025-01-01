#include "gameobjectcomponent.h"

GameObjectComponent::GameObjectComponent() : active(true) {};

bool GameObjectComponent::isActive()
{
    return this->active;
}

void GameObjectComponent::setActive(bool active)
{
    this->active = active;
}

void GameObjectComponent::toggle()
{
    this->active = !this->active;
}
