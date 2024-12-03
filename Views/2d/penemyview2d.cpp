#include "PEnemyView2D.h"
#include <QPainter>
#include "penemyobject.h"

PEnemyView2D::PEnemyView2D(QGraphicsItem *parent) : CharacterView2D(parent)  {}

void PEnemyView2D::draw(std::shared_ptr<const GameObject> go) {

    auto penemyObject = std::dynamic_pointer_cast<const PEnemyObject>(go);
    if (!penemyObject) return;

    float x = penemyObject->getPEnemy().getXPos()*50;
    float y = penemyObject->getPEnemy().getYPos()*50;
    setPos(x+25,y+25);

    // Trigger a repaint
    QGraphicsItem::update();
}

QRectF PEnemyView2D::boundingRect() const {
    return QRectF(-10, -10, 20, 20); // Adjust based on shape size
}

void PEnemyView2D::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setBrush(Qt::green); // Set arbitrary shape color
    painter->setPen(Qt::NoPen);  // No border
    painter->drawEllipse(-10,-10, 20, 20); // Circle with radius 10
}
