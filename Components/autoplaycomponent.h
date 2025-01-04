#ifndef AUTOPLAYCOMPONENT_H
#define AUTOPLAYCOMPONENT_H

#include "gameobjectcomponent.h"
#include "world.h"
#include "pathfinder_class.h"

class Node : public Tile{
public:
    Node(Tile &t) : Tile(t), f(0), g(0), h(0), visited(false), closed(false), prev(nullptr) {};

    float f, g, h;
    bool visited, closed;
    Node* prev;
};

class LevelObject;
class PlayerObject;

class AutoPlayComponent : public GameObjectComponent
{
public:
    AutoPlayComponent();
    ~AutoPlayComponent();

    const Tile* getTarget() const;
    void setTarget(const Tile* t);

    void step_component(GameObject& owner, qint64 deltaT = 0) override;

private:


    const Tile* target;
    PathFinder<Node, Tile>* pf;

    std::vector<Node> nodes;

    std::vector<int> path;
    void updatePath(PlayerObject& player, std::shared_ptr<LevelObject> lo);

    const Tile* chooseTarget(PlayerObject& player, std::shared_ptr<LevelObject> lo);
    const Tile* nearestEnemy(PlayerObject& player, std::shared_ptr<LevelObject> lo);
    const Tile* nearestHealth(PlayerObject& player, std::shared_ptr<LevelObject> lo);
    const Tile* nearestExit(PlayerObject& player, std::shared_ptr<LevelObject> lo);


};

#endif // AUTOPLAYCOMPONENT_H
