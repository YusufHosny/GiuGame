#ifndef GAMEOBJECTCOMPONENT_H
#define GAMEOBJECTCOMPONENT_H

#include <QIntegerForSize>

class GameObject;

/*
 * A GameObjectComponent is a reusable component that can be
 * attached to a game object, which is updated in the step function
 * e.g. collisionManagerComponent, animationComponent, colliderComponent
*/
class GameObjectComponent
{

protected:
    bool active;

public:
    GameObjectComponent();

    virtual ~GameObjectComponent() {};

    virtual void step_component(GameObject& owner, qint64 deltaT = 0) = 0;

    bool isActive();
    void setActive(bool active);
    void toggle();
};

#endif // GAMEOBJECTCOMPONENT_H
