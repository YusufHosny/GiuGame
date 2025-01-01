#include "healthpackview2d.h"
#include "healthpackobject.h"
#include "giugameconfig.h"
#include <QPainter>

HealthPackView2D::HealthPackView2D(QGraphicsItem *parent) : ItemView(parent)  {}

void HealthPackView2D::draw(std::shared_ptr<const GameObject> go) {

    auto HPObject = std::dynamic_pointer_cast<const HealthPackObject>(go);
    assert(HPObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = HPObject->getHP().getXPos()*tileSideLen;
    float y = HPObject->getHP().getYPos()*tileSideLen;
    this->setPos(x+tileSideLen/2,y+tileSideLen/2);

    QGraphicsItem::update();
}

void HealthPackView2D::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::red, 2));
    painter->drawLine(-10, 0, 10, 0);
    painter->drawLine(0, -10, 0, 10);
}
