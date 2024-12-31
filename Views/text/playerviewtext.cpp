#include "playerviewtext.h"
#include <QPainter>
#include "playerobject.h"

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
    painter->setBrush(Qt::gray);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-10,-10, 20, 20);
}
