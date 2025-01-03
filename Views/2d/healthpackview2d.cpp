#include "healthpackview2d.h"
#include "healthpackobject.h"
#include "giugameconfig.h"
#include "animationcomponent.h"
#include "spriteloader.h"
#include <QPainter>

HealthPackView2d::HealthPackView2d(QGraphicsItem *parent) : AnimatedItemView(parent)  {
    if(this->getSprites().empty())
        this->loadSprites();
}

// sprites loaded in enum order
void HealthPackView2d::loadSprites() {
    this->getSprites().emplace(HealthPackObject::IDLE, SpriteLoader::load(":/assets/sprites2d/items/health.png"));

}

std::map<unsigned int, std::vector<QPixmap>> HealthPackView2d::sprites;
std::map<unsigned int, std::vector<QPixmap>>& HealthPackView2d::getSprites() {
    return HealthPackView2d::sprites;
}

void HealthPackView2d::draw(std::shared_ptr<const GameObject> go) {

    auto HPObject = std::dynamic_pointer_cast<const HealthPackObject>(go);
    assert(HPObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = HPObject->getHP().getXPos()*tileSideLen;
    float y = HPObject->getHP().getYPos()*tileSideLen;
    this->setPos(x+tileSideLen/2,y+tileSideLen/2);

    auto ac = HPObject->getComponent<AnimationComponent>();
    this->animationState = ac->getAnimation();
    this->frameId = ac->getFrame();

    QGraphicsItem::update();
}
