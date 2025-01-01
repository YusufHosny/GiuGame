#include "benemyview2d.h"
#include "benemyobject.h"
#include "giugameconfig.h"
#include <QPainter>

BEnemyView2d::BEnemyView2d(QGraphicsItem *parent) : ItemView(parent)  {}

void BEnemyView2d::draw(std::shared_ptr<const GameObject> go) {

    auto benemyObject = std::dynamic_pointer_cast<const BEnemyObject>(go);
    assert(benemyObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = benemyObject->getEnemy().getXPos()*tileSideLen;
    float y = benemyObject->getEnemy().getYPos()*tileSideLen;
    setPos(x+tileSideLen/2,y+tileSideLen/2);

    QGraphicsItem::update();
}


void BEnemyView2d::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-10,-10, 20, 20);
}
