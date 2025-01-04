#include "giugameobject.h"
#include "levelobject.h"

GiuGameObject::GiuGameObject() : GameObject("TopLevelObject") {

}

void GiuGameObject::nextLevel(QString nextLevelPath)
{
    this->nextLevelObject = this->wl.load(nextLevelPath);
}

void GiuGameObject::init()
{

}

void GiuGameObject::step(qint64 deltaT, std::set<GameInput> inputs)
{
    if(this->nextLevelObject) {
        this->removeChild(this->findChildren<LevelObject>().at(0));
        this->addChild(this->nextLevelObject);
        this->nextLevelObject->init_impl();
        this->nextLevelObject = nullptr;
    }
}

std::string GiuGameObject::dumpData() const
{
    return ""; // TODO
}
