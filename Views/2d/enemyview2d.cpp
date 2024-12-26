#include "EnemyView2D.h"
#include <QPainter>
#include "enemyobject.h"

EnemyView2D::EnemyView2D(QGraphicsItem *parent) : ItemView2d(parent)  {}

void EnemyView2D::draw(std::shared_ptr<const GameObject> go) {

    auto enemyObject = std::dynamic_pointer_cast<const EnemyObject>(go);
    assert(enemyObject);

    float x = enemyObject->getEnemy().getXPos()*50;
    float y = enemyObject->getEnemy().getYPos()*50;
    setPos(x+25,y+25);

    QGraphicsItem::update();
}

QRectF EnemyView2D::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void EnemyView2D::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-10,-10, 20, 20);
}
