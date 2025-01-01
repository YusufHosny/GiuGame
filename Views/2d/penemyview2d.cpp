#include "PEnemyView2D.h"
#include "giugameconfig.h"
#include "penemyobject.h"
#include <QPainter>

PEnemyView2D::PEnemyView2D(QGraphicsItem *parent) : ItemView(parent)  {}

void PEnemyView2D::draw(std::shared_ptr<const GameObject> go) {

    auto penemyObject = std::dynamic_pointer_cast<const PEnemyObject>(go);
    assert(penemyObject);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = penemyObject->getPEnemy().getXPos()*tileSideLen;
    float y = penemyObject->getPEnemy().getYPos()*tileSideLen;
    this->setPos(x+tileSideLen/2,y+tileSideLen/2);

    QGraphicsItem::update();
}

void PEnemyView2D::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::green);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-10,-10, 20, 20);
}
