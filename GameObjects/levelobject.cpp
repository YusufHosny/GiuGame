#include "levelobject.h"

LevelObject::LevelObject(std::vector<std::unique_ptr<Tile>> tiles, std::vector<std::unique_ptr<Tile>> healthPacks, int rows, int cols):
    tiles(std::move(tiles)), healthPacks(std::move(healthPacks)), rows(rows), cols(cols) {}

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
