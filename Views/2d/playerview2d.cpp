#include "playerview2d.h"
#include "giugameconfig.h"
#include "playerobject.h"
#include "spriteloader.h"
#include "animationcomponent.h"
#include <QPainter>


PlayerView2d::PlayerView2d(QGraphicsItem *parent) : ItemView(parent)  {
    if(PlayerView2d::sprites.empty())
        PlayerView2d::loadSprites();
}

// sprites loaded in enum order
void PlayerView2d::loadSprites() {
    // idle sprites
    PlayerView2d::sprites.emplace(PlayerObject::IDLEUP, SpriteLoader::load(":/assets/sprites2d/player/idleup.png"));
    PlayerView2d::sprites.emplace(PlayerObject::IDLEDOWN, SpriteLoader::load(":/assets/sprites2d/player/idledown.png"));
    PlayerView2d::sprites.emplace(PlayerObject::IDLELEFT, SpriteLoader::load(":/assets/sprites2d/player/idleside.png"));
    PlayerView2d::sprites.emplace(PlayerObject::IDLERIGHT, SpriteLoader::load(":/assets/sprites2d/player/idleside.png", true)); // flip for right frame

    // walking spritesheet
    PlayerView2d::sprites.emplace(PlayerObject::WALKUP, SpriteLoader::load(":/assets/sprites2d/player/walkup.png"));
    PlayerView2d::sprites.emplace(PlayerObject::WALKDOWN, SpriteLoader::load(":/assets/sprites2d/player/walkdown.png"));
    PlayerView2d::sprites.emplace(PlayerObject::WALKLEFT, SpriteLoader::load(":/assets/sprites2d/player/walkside.png"));
    PlayerView2d::sprites.emplace(PlayerObject::WALKRIGHT, SpriteLoader::load(":/assets/sprites2d/player/walkside.png", true)); // flip for right frame

    // etc
    PlayerView2d::sprites.emplace(PlayerObject::FIGHTING, SpriteLoader::load(":/assets/sprites2d/player/fight.png"));
    PlayerView2d::sprites.emplace(PlayerObject::DYING, SpriteLoader::load(":/assets/sprites2d/player/dying.png"));

}

std::map<unsigned int, std::vector<QPixmap>> PlayerView2d::sprites;

void PlayerView2d::draw(std::shared_ptr<const GameObject> go) {

    auto playerObject = std::dynamic_pointer_cast<const PlayerObject>(go);
    assert(playerObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = playerObject->getProtagonist().getXPos()*tileSideLen;
    float y = playerObject->getProtagonist().getYPos()*tileSideLen;
    this->setPos(x+tileSideLen/2,y+tileSideLen/2);

    if(auto ac = playerObject->getComponent<AnimationComponent>()) {
        this->animationState = ac->getAnimation();
        this->frameId = ac->getFrame();
    }
    else {
        this->animationState = PlayerObject::IDLEDOWN;
        this->frameId = 0;
    }


    QGraphicsItem::update();
}


void PlayerView2d::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(this->boundingRect().toRect(), PlayerView2d::sprites.at(this->animationState).at(this->frameId));
}
