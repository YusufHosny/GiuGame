#include "playerviewtext.h"
#include <QPainter>
#include "playerobject.h"
#include "giugameconfig.h"

PlayerViewText::PlayerViewText(QGraphicsItem *parent) : ItemViewText(parent)  {}

void PlayerViewText::draw(std::shared_ptr<const GameObject> go) {

    auto playerObject = std::dynamic_pointer_cast<const PlayerObject>(go);
    assert(playerObject);

    float x = playerObject->getProtagonist().getXPos()*50;
    float y = playerObject->getProtagonist().getYPos()*50;
    this->setPos(x+25,y+25);

    QGraphicsItem::update();
}

QRectF PlayerViewText::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void PlayerViewText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(GiuGameConfig::getInstance().configText.bgColor);
    painter->setPen(GiuGameConfig::getInstance().configText.bgColor);
    painter->drawRect(-25,-25, 50, 50);

    painter->setBrush(Qt::blue);
    painter->setPen(Qt::blue);
    painter->setFont(GiuGameConfig::getInstance().configText.textFont);
    painter->drawText(-10,-10, 20, 20, Qt::AlignCenter, "P");
}
