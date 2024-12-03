#include "PlayerView2D.h"
#include <QPainter>
#include "playerobject.h"

PlayerView2D::PlayerView2D(QGraphicsItem *parent) : CharacterView2D(parent)  {}

void PlayerView2D::draw(std::shared_ptr<const GameObject> go) {

    auto playerObject = std::dynamic_pointer_cast<const PlayerObject>(go);
    if (!playerObject) return;

    float x = playerObject->getProtagonist().getXPos()*50;
    float y = playerObject->getProtagonist().getYPos()*50;
    setPos(x+25,y+25);

    QGraphicsItem::update();
}

QRectF PlayerView2D::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void PlayerView2D::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::blue);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-10,-10, 20, 20);
}
