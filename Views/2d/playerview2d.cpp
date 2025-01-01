#include "PlayerView2D.h"
#include "giugameconfig.h"
#include "playerobject.h"
#include <QPainter>

PlayerView2d::PlayerView2d(QGraphicsItem *parent) : ItemView(parent)  {}

void PlayerView2d::draw(std::shared_ptr<const GameObject> go) {

    auto playerObject = std::dynamic_pointer_cast<const PlayerObject>(go);
    assert(playerObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = playerObject->getProtagonist().getXPos()*tileSideLen;
    float y = playerObject->getProtagonist().getYPos()*tileSideLen;
    this->setPos(x+tileSideLen/2,y+tileSideLen/2);

    QGraphicsItem::update();
}


void PlayerView2d::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::blue);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-10,-10, 20, 20);
}
