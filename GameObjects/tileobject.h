#ifndef TILEOBJECT_H
#define TILEOBJECT_H

#include "GameObject.h"
#include "world.h"

class TileObject : public GameObject
{
protected:
    TileObject(std::string label);

public:
    virtual const Tile& getTile() const = 0;
};

#endif // TILEOBJECT_H
