#include "penemyview2d.h"
#include "giugameconfig.h"
#include "penemyobject.h"
#include "spriteloader.h"
#include "animationcomponent.h"
#include <QPainter>

PEnemyView2d::PEnemyView2d(QGraphicsItem *parent) : AnimatedItemView(parent)  {
    if(this->getSprites().empty())
        this->loadSprites();
}

std::map<unsigned int, std::vector<QPixmap>> PEnemyView2d::sprites;
std::map<unsigned int, std::vector<QPixmap>>& PEnemyView2d::getSprites() {
    return PEnemyView2d::sprites;
}

// sprites loaded in enum order
void PEnemyView2d::loadSprites() {
    this->getSprites().emplace(PEnemyObject::UP, SpriteLoader::load(":/assets/sprites2d/enemies/penemy/up.png"));
    this->getSprites().emplace(PEnemyObject::DOWN, SpriteLoader::load(":/assets/sprites2d/enemies/penemy/down.png"));
    this->getSprites().emplace(PEnemyObject::LEFT, SpriteLoader::load(":/assets/sprites2d/enemies/penemy/side.png"));
    this->getSprites().emplace(PEnemyObject::RIGHT, SpriteLoader::load(":/assets/sprites2d/enemies/penemy/side.png", true)); // flip for right frame

}

void PEnemyView2d::draw(std::shared_ptr<const GameObject> go) {

    auto penemyObject = std::dynamic_pointer_cast<const PEnemyObject>(go);
    assert(penemyObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = penemyObject->getPEnemy().getXPos()*tileSideLen;
    float y = penemyObject->getPEnemy().getYPos()*tileSideLen;
    this->setPos(x+tileSideLen/2,y+tileSideLen/2);

    auto ac = penemyObject->getComponent<AnimationComponent>();
    this->animationState = ac->getAnimation();
    this->frameId = ac->getFrame();

    QGraphicsItem::update();
}


