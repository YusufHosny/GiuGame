#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <functional>
#include "gameobjectcomponent.h"

class ColliderComponent: public GameObjectComponent
{
private:
    std::function<void(std::shared_ptr<GameObject>)> onCollision;
    std::function<void(std::shared_ptr<const GameObject>)> getPosition;
    bool hasCollided;

public:
    ColliderComponent(std::function<void(std::shared_ptr<GameObject>)> onCollision, std::function<void(std::shared_ptr<const GameObject>)> getPosition):
        onCollision(onCollision), getPosition(getPosition) {};
    void notifyCollision();

    void step_component(const GameObject& owner) override;
};

#endif // COLLIDERCOMPONENT_H
