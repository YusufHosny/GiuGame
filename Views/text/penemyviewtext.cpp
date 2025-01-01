#include "penemyviewtext.h"
#include <QPainter>
#include "penemyobject.h"
#include "giugameconfig.h"

PEnemyViewText::PEnemyViewText(QGraphicsItem *parent) : ItemViewText(parent)  {}

void PEnemyViewText::draw(std::shared_ptr<const GameObject> go) {

    auto penemyObject = std::dynamic_pointer_cast<const PEnemyObject>(go);
    assert(penemyObject);

    float x = penemyObject->getPEnemy().getXPos()*50;
    float y = penemyObject->getPEnemy().getYPos()*50;
    this->setPos(x+25,y+25);

    QGraphicsItem::update();
}

QRectF PEnemyViewText::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void PEnemyViewText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(GiuGameConfig::getInstance().configText.bgColor);
    painter->setPen(GiuGameConfig::getInstance().configText.bgColor);
    painter->drawRect(-25,-25, 50, 50);

    painter->setBrush(QColorConstants::Svg::purple);
    painter->setPen(QColorConstants::Svg::purple);
    painter->setFont(GiuGameConfig::getInstance().configText.textFont);
    painter->drawText(-10,-10, 20, 20, Qt::AlignCenter, "V");
}
