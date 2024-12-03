#include "EnemyView2D.h"
#include <QPainter>
#include "enemyobject.h"

EnemyView2D::EnemyView2D(QGraphicsItem *parent) : CharacterView2D(parent)  {}

void EnemyView2D::draw(std::shared_ptr<const GameObject> go) {

    auto enemyObject = std::dynamic_pointer_cast<const EnemyObject>(go);
    if (!enemyObject) return;

    float x = enemyObject->getEnemy().getXPos()*50;
    float y = enemyObject->getEnemy().getYPos()*50;
    setPos(x+25,y+25);

    // Trigger a repaint
    QGraphicsItem::update();
}

QRectF EnemyView2D::boundingRect() const {
    return QRectF(-10, -10, 20, 20); // Adjust based on shape size
}

void EnemyView2D::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    painter->setBrush(Qt::green); // Set arbitrary shape color
    painter->setPen(Qt::NoPen);  // No border
    painter->drawEllipse(-10,-10, 20, 20); // Circle with radius 10
}
