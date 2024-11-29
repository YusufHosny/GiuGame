#include "levelobject.h"
#include "collisionmanagercomponent.h"

LevelObject::LevelObject(std::vector<std::unique_ptr<Tile>> tiles, int rows, int cols):
    tiles(std::move(tiles)), rows(rows), cols(cols), GameObject("Level") {}

void LevelObject::init()
{
    this->components.emplace_back(new CollisionManagerComponent());
}

void LevelObject::step(qint64 deltaT, std::set<GameInput> inputs)
{

}

std::string LevelObject::dumpData() const
{
    return ""; // TODO
}
