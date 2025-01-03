#include "playerview2d.h"
#include "giugameconfig.h"
#include "playerobject.h"
#include "spriteloader.h"
#include "animationcomponent.h"
#include <QPainter>


PlayerView2d::PlayerView2d(QGraphicsItem *parent) : AnimatedItemView(parent)  {
    if(this->getSprites().empty())
        this->loadSprites();
}

std::map<unsigned int, std::vector<QPixmap>> PlayerView2d::sprites;
std::map<unsigned int, std::vector<QPixmap>>& PlayerView2d::getSprites() {
    return PlayerView2d::sprites;
}


// sprites loaded in enum order
void PlayerView2d::loadSprites() {
    // idle sprites
    this->getSprites().emplace(PlayerObject::IDLEUP, SpriteLoader::load(":/assets/sprites2d/player/idleup.png"));
    this->getSprites().emplace(PlayerObject::IDLEDOWN, SpriteLoader::load(":/assets/sprites2d/player/idledown.png"));
    this->getSprites().emplace(PlayerObject::IDLELEFT, SpriteLoader::load(":/assets/sprites2d/player/idleside.png"));
    this->getSprites().emplace(PlayerObject::IDLERIGHT, SpriteLoader::load(":/assets/sprites2d/player/idleside.png", true)); // flip for right frame

    // walking spritesheet
    this->getSprites().emplace(PlayerObject::WALKUP, SpriteLoader::load(":/assets/sprites2d/player/walkup.png"));
    this->getSprites().emplace(PlayerObject::WALKDOWN, SpriteLoader::load(":/assets/sprites2d/player/walkdown.png"));
    this->getSprites().emplace(PlayerObject::WALKLEFT, SpriteLoader::load(":/assets/sprites2d/player/walkside.png"));
    this->getSprites().emplace(PlayerObject::WALKRIGHT, SpriteLoader::load(":/assets/sprites2d/player/walkside.png", true)); // flip for right frame

    // etc
    this->getSprites().emplace(PlayerObject::FIGHTING, SpriteLoader::load(":/assets/sprites2d/player/fight.png"));
    this->getSprites().emplace(PlayerObject::DYING, SpriteLoader::load(":/assets/sprites2d/player/dying.png"));

}

void PlayerView2d::draw(std::shared_ptr<const GameObject> go) {

    auto playerObject = std::dynamic_pointer_cast<const PlayerObject>(go);
    assert(playerObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = playerObject->getProtagonist().getXPos()*tileSideLen;
    float y = playerObject->getProtagonist().getYPos()*tileSideLen;
    this->setPos(x+tileSideLen/2,y+tileSideLen/2);

    auto ac = playerObject->getComponent<AnimationComponent>();
    this->animationState = ac->getAnimation();
    this->frameId = ac->getFrame();

    QGraphicsItem::update();
}


