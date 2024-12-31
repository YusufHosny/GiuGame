#include "healthpackviewtext.h"

#include <QPainter>
#include "healthpackobject.h"

HealthPackViewText::HealthPackViewText(QGraphicsItem *parent) : ItemViewText(parent)  {}

void HealthPackViewText::draw(std::shared_ptr<const GameObject> go) {

    auto HPObject = std::dynamic_pointer_cast<const HealthPackObject>(go);
    assert(HPObject);

    float x = HPObject->getHP().getXPos()*50;
    float y = HPObject->getHP().getYPos()*50;
    this->setPos(x+25,y+25);

    QGraphicsItem::update();
}

QRectF HealthPackViewText::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void HealthPackViewText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::red, 2));
    painter->drawLine(-10, 0, 10, 0);
    painter->drawLine(0, -10, 0, 10);
}
