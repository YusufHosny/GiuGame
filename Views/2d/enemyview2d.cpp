#include "EnemyView2D.h"
#include "enemyobject.h"
#include "giugameconfig.h"
#include <QPainter>

EnemyView2d::EnemyView2d(QGraphicsItem *parent) : ItemView(parent)  {}

void EnemyView2d::draw(std::shared_ptr<const GameObject> go) {

    auto enemyObject = std::dynamic_pointer_cast<const EnemyObject>(go);
    assert(enemyObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = enemyObject->getEnemy().getXPos()*tileSideLen;
    float y = enemyObject->getEnemy().getYPos()*tileSideLen;
    setPos(x+tileSideLen/2,y+tileSideLen/2);

    QGraphicsItem::update();
}

void EnemyView2d::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-10,-10, 20, 20);
}
