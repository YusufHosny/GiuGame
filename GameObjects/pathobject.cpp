#include "pathobject.h"
#include "giugameconfig.h"

PathObject::PathObject(int x, int y) : TileObject("Path"), tile(x, y, GiuGameConfig::getInstance().pathBaseOpacity) {}

const Tile& PathObject::getTile() const {
    return this->tile;
}

void PathObject::init()
{
    this->pathDecayCooldown = GiuGameConfig::getInstance().pathOpacDecayCooldown;
    this->pathDecayCooldownLeft = this->pathDecayCooldown;
}

void PathObject::step(qint64 deltaT, std::set<GameInput> inputs)
{
    if(this->pathDecayCooldownLeft > 0) {
        this->pathDecayCooldownLeft -= deltaT;
    }
    else {
        float newVal = this->tile.getValue() - GiuGameConfig::getInstance().pathOpacityDecay;
        if(newVal > 0) {
            this->tile.setValue(newVal);
            this->pathDecayCooldownLeft = this->pathDecayCooldown;
        }
        else {
            this->tile.setValue(0);
        }
    }

}

std::string PathObject::dumpData() const
{
    return ""; // TODO
}
