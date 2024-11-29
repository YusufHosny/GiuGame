#ifndef GAMEOBJECTCOMPONENT_H
#define GAMEOBJECTCOMPONENT_H

#include "GameObject.h"

/*
 * A GameObjectComponent is a reusable component that can be
 * attached to a game object, which is updated in the step function
 * e.g. collisionManagerComponent, animationComponent, colliderComponent
*/
class GameObjectComponent
{

public:
    GameObjectComponent() {};

    virtual ~GameObjectComponent() {};

    virtual void step_component(GameObject& owner) = 0;
};

#endif // GAMEOBJECTCOMPONENT_H
