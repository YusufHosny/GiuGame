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
    this->zoomStatus = 0;
    this->cameraReset = false;
    this->cameraMovement = Direction::NONE;
    for(auto &input: inputs) {
        if(input.type == GameInputType::ZOOM) {
            if(input.parameter == 0) {
                this->zoomStatus = -1;
            }
            else {
                this->zoomStatus = 1;
            }
        }
        else if(input.type == GameInputType::RESETCAMERA) {
            this->cameraReset = true;
        }
        else if(input.type == GameInputType::CAMERAMOVE) {
            this->cameraMovement = static_cast<Direction>(input.parameter);
        }
    }
}

std::string LevelObject::dumpData() const
{
    return ""; // TODO
}

const std::vector<std::unique_ptr<Tile> > &LevelObject::getTiles() const
{
    return tiles;
}

const std::unique_ptr<Tile> &LevelObject::getTile(int x, int y)
{
    return tiles.at(y*cols + x);
}

const int LevelObject::getRows() const
{
    return rows;
}

const int LevelObject::getCols() const
{
    return cols;
}

int LevelObject::getZoomStatus() const
{
    return zoomStatus;
}

bool LevelObject::getCameraReset() const
{
    return cameraReset;
}

Direction LevelObject::getCameraMovement() const
{
    return cameraMovement;
}
