#ifndef AUTOPLAYCOMPONENT_H
#define AUTOPLAYCOMPONENT_H

#include "gameobjectcomponent.h"
#include "world.h"

class LevelObject;

class AutoPlayComponent : public GameObjectComponent
{
public:
    AutoPlayComponent();

    void step_component(GameObject& owner, qint64 deltaT = 0) override;

private:
    class Node : public Tile{
    public:
        Node(Tile &t) : Tile(t), f(0), g(0), h(0), visited(false), closed(false), prev(nullptr) {};

        float f, g, h;
        bool visited, closed;
        Node* prev;
    };

    std::function<float(const Tile& t1, const Tile& t2)> heurdist;
    std::function<float(const Tile& t1, const Tile& t2)> cost;
    std::function<bool(const Node& t1, const Node& t2)> compareNodes;
};

#endif // AUTOPLAYCOMPONENT_H
