#include "levelobject.h"

LevelObject::LevelObject(std::vector<std::unique_ptr<Tile>> tiles): tiles(std::move(tiles)) {}

void LevelObject::init()
{

}

void LevelObject::step(qint64 deltaT, std::set<GameInput> inputs)
{

}

std::string LevelObject::dumpData() const
{
    return ""; // TODO
}
