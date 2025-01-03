#include "benemyview2d.h"
#include "benemyobject.h"
#include "giugameconfig.h"
#include "spriteloader.h"
#include "animationcomponent.h"
#include <QPainter>

BEnemyView2d::BEnemyView2d(QGraphicsItem *parent) : AnimatedItemView(parent)  {
    if(this->getSprites().empty())
        this->loadSprites();
}

std::map<unsigned int, std::vector<QPixmap>> BEnemyView2d::sprites;
std::map<unsigned int, std::vector<QPixmap>>& BEnemyView2d::getSprites() {
    return BEnemyView2d::sprites;
}

// sprites loaded in enum order
void BEnemyView2d::loadSprites() {
    this->getSprites().emplace(BEnemyObject::IDLE, SpriteLoader::load(":/assets/sprites2d/enemies/benemy/idle.png"));
    this->getSprites().emplace(BEnemyObject::BLINK, SpriteLoader::load(":/assets/sprites2d/enemies/benemy/down.png"));
}

void BEnemyView2d::draw(std::shared_ptr<const GameObject> go) {

    auto benemyObject = std::dynamic_pointer_cast<const BEnemyObject>(go);
    assert(benemyObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = benemyObject->getEnemy().getXPos()*tileSideLen;
    float y = benemyObject->getEnemy().getYPos()*tileSideLen;
    setPos(x+tileSideLen/2,y+tileSideLen/2);

    auto ac = benemyObject->getComponent<AnimationComponent>();
    this->animationState = ac->getAnimation();
    this->frameId = ac->getFrame();

    QGraphicsItem::update();
}
