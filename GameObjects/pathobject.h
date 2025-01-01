#ifndef PATHOBJECT_H
#define PATHOBJECT_H

#include "tileobject.h"

class PathObject : public TileObject
{

private:
    PathObject(const PathObject &) = delete;
    PathObject &operator=(const PathObject &) = delete;

    PathObject(int x, int y);

    Tile tile;

    qint64 pathDecayCooldownLeft;
    qint64 pathDecayCooldown;

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    const Tile& getTile() const override;

    friend class PathTracerComponent;
};

#endif // PATHOBJECT_H
