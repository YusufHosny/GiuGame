#ifndef GAMEOBJECTCOMPONENT_H
#define GAMEOBJECTCOMPONENT_H


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

    virtual void step_component(GameObject& owner) = 0;

    bool isActive();
    void setActive(bool active);
    void toggle();
};

#endif // GAMEOBJECTCOMPONENT_H
