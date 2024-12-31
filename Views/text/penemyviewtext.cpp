#include "penemyviewtext.h"
#include <QPainter>
#include "penemyobject.h"

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
    painter->setBrush(QColorConstants::Svg::purple);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-10,-10, 20, 20);
}
