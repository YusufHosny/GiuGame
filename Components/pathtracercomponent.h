#ifndef PATHTRACERCOMPONENT_H
#define PATHTRACERCOMPONENT_H

#include "gameobjectcomponent.h"
#include "world.h"
#include "tileobject.h"

class PathTracerComponent : public GameObjectComponent
{
private:
    int xprev, yprev;

public:
    PathTracerComponent();

    void setCurrent(const Tile& tile);
    void reset(TileObject& owner);

    void step_component(GameObject& owner, qint64 deltaT = 0) override;
};

#endif // PATHTRACERCOMPONENT_H
