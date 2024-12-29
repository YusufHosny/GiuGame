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
    }
}

std::string LevelObject::dumpData() const
{
    return ""; // TODO
}
