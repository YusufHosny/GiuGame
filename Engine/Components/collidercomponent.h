#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <functional>
#include "gameobjectcomponent.h"
#include <memory>

class ColliderComponent: public GameObjectComponent
{
private:
    ColliderComponent() = delete;

    std::function<void(std::shared_ptr<GameObject>)> onCollision;
    std::function<std::array<int, 2>()> getPositionImpl;

public:
    ColliderComponent(std::function<void(std::shared_ptr<GameObject>)> onCollision, std::function<std::array<int, 2>()> getPosition);
    void notifyCollision(std::shared_ptr<GameObject> other);

    std::array<int, 2> getPosition();

    void step_component(GameObject& owner, qint64 deltaT = 0) override;
};

#endif // COLLIDERCOMPONENT_H
