#include "doorview2d.h"
#include "doorobject.h"
#include "giugameconfig.h"
#include "animationcomponent.h"
#include "spriteloader.h"
#include <QPainter>

DoorView2d::DoorView2d(QGraphicsItem *parent) : AnimatedItemView(parent)  {
    if(this->getSprites().empty())
        this->loadSprites();
}

// sprites loaded in enum order
void DoorView2d::loadSprites() {
    this->getSprites().emplace(DoorObject::IDLE, SpriteLoader::load(":/assets/sprites2d/items/portal.png"));

}

std::map<unsigned int, std::vector<QPixmap>> DoorView2d::sprites;
std::map<unsigned int, std::vector<QPixmap>>& DoorView2d::getSprites() {
    return DoorView2d::sprites;
}

void DoorView2d::draw(std::shared_ptr<const GameObject> dobj) {

    auto dObject = std::dynamic_pointer_cast<const DoorObject>(dobj);
    assert(dObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = dObject->getTile().getXPos()*tileSideLen;
    float y = dObject->getTile().getYPos()*tileSideLen;
    this->setPos(x+tileSideLen/2,y+tileSideLen/2);

    auto ac = dObject->getComponent<AnimationComponent>();
    this->animationState = ac->getAnimation();
    this->frameId = ac->getFrame();

    QGraphicsItem::update();
}
