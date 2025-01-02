#include "collisionmanagercomponent.h"
#include "collidercomponent.h"
#include "gameobject.h"

CollisionManagerComponent::CollisionManagerComponent() {}

void CollisionManagerComponent::step_component(GameObject &owner, qint64 deltaT)
{
    auto collisionObjects = owner.childrenWithActiveComponent<ColliderComponent>();
    for(auto first = collisionObjects.begin(); first != collisionObjects.end(); first++) {
        for(auto second = first + 1; second != collisionObjects.end(); second++) {
            std::shared_ptr<GameObject> child = *first;
            std::shared_ptr<GameObject> otherchild = *second;

            if(child != otherchild) {
                std::shared_ptr<ColliderComponent> col1, col2;
                col1 = child->getComponent<ColliderComponent>();
                col2 = otherchild->getComponent<ColliderComponent>();

                std::array<int, 2> pos1, pos2;
                pos1 = col1->getPosition();
                pos2 = col2->getPosition();

                if(pos1[0] == pos2[0] && pos1[1] == pos2[1]) {
                    col1->notifyCollision(otherchild);
                    col2->notifyCollision(child);
                }
            }
        }
    }
}
