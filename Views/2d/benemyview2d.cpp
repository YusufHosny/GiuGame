#include "benemyview2d.h"
#include <QPainter>
#include "benemyobject.h"

BEnemyView2D::BEnemyView2D(QGraphicsItem *parent) : ItemView2d(parent)  {}

void BEnemyView2D::draw(std::shared_ptr<const GameObject> go) {

    auto enemyObject = std::dynamic_pointer_cast<const BEnemyObject>(go);
    assert(enemyObject);

    float x = enemyObject->getEnemy().getXPos()*50;
    float y = enemyObject->getEnemy().getYPos()*50;
    setPos(x+25,y+25);

    QGraphicsItem::update();
}

QRectF BEnemyView2D::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void BEnemyView2D::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-10,-10, 20, 20);
}
