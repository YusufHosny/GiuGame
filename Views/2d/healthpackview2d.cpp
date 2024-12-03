#include "healthpackview2d.h"

#include <QPainter>
#include "healthpackobject.h"

HealthPackView2D::HealthPackView2D(QGraphicsItem *parent) : CharacterView2D(parent)  {}

void HealthPackView2D::draw(std::shared_ptr<const GameObject> go) {

    auto HPObject = std::dynamic_pointer_cast<const HealthPackObject>(go);
    if (!HPObject) return;

    float x = HPObject->getHP().getXPos()*50;
    float y = HPObject->getHP().getYPos()*50;
    setPos(x+25,y+25);

    QGraphicsItem::update();
}

QRectF HealthPackView2D::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void HealthPackView2D::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::red, 2));
    painter->drawLine(-10, 0, 10, 0);
    painter->drawLine(0, -10, 0, 10);
}
