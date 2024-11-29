#ifndef COLLISIONMANAGERCOMPONENT_H
#define COLLISIONMANAGERCOMPONENT_H

#include "gameobjectcomponent.h"

class CollisionManagerComponent: public GameObjectComponent
{
public:
    CollisionManagerComponent();

    void step_component(GameObject& owner) override;
};

#endif // COLLISIONMANAGERCOMPONENT_H
