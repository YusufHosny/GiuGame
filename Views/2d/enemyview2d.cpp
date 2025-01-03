#include "enemyview2d.h"
#include "enemyobject.h"
#include "giugameconfig.h"
#include "spriteloader.h"
#include "animationcomponent.h"
#include <QPainter>

EnemyView2d::EnemyView2d(QGraphicsItem *parent) : AnimatedItemView(parent)  {
    if(this->getSprites().empty())
        this->loadSprites();
}

void EnemyView2d::draw(std::shared_ptr<const GameObject> go) {

    auto enemyObject = std::dynamic_pointer_cast<const EnemyObject>(go);
    assert(enemyObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = enemyObject->getEnemy().getXPos()*tileSideLen;
    float y = enemyObject->getEnemy().getYPos()*tileSideLen;
    setPos(x+tileSideLen/2,y+tileSideLen/2);

    auto ac = enemyObject->getComponent<AnimationComponent>();
    this->animationState = ac->getAnimation();
    this->frameId = ac->getFrame();

    QGraphicsItem::update();
}

std::map<unsigned int, std::vector<QPixmap>> EnemyView2d::sprites;
std::map<unsigned int, std::vector<QPixmap>>& EnemyView2d::getSprites() {
    return EnemyView2d::sprites;
}

// sprites loaded in enum order
void EnemyView2d::loadSprites() {
    this->getSprites().emplace(EnemyObject::UP, SpriteLoader::load(":/assets/sprites2d/enemies/enemy/up.png"));
    this->getSprites().emplace(EnemyObject::DOWN, SpriteLoader::load(":/assets/sprites2d/enemies/enemy/down.png"));
    this->getSprites().emplace(EnemyObject::LEFT, SpriteLoader::load(":/assets/sprites2d/enemies/enemy/side.png"));
    this->getSprites().emplace(EnemyObject::RIGHT, SpriteLoader::load(":/assets/sprites2d/enemies/enemy/side.png", true)); // flip for right frame

}
