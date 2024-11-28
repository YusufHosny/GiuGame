#ifndef COLLISIONMANAGERCOMPONENT_H
#define COLLISIONMANAGERCOMPONENT_H

#include "gameobjectcomponent.h"

class CollisionManagerComponent: public GameObjectComponent
{
public:
    void checkCollisions();

    void step_component(const GameObject& owner) override;
};

#endif // COLLISIONMANAGERCOMPONENT_H
