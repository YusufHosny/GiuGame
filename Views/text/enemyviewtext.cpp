#include "enemyviewtext.h"
#include <QPainter>
#include "enemyobject.h"
#include "giugameconfig.h"

EnemyViewText::EnemyViewText(QGraphicsItem *parent) : ItemViewText(parent)  {}

void EnemyViewText::draw(std::shared_ptr<const GameObject> go) {

    auto enemyObject = std::dynamic_pointer_cast<const EnemyObject>(go);
    assert(enemyObject);

    float x = enemyObject->getEnemy().getXPos()*50;
    float y = enemyObject->getEnemy().getYPos()*50;
    setPos(x+25,y+25);

    QGraphicsItem::update();
}

QRectF EnemyViewText::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void EnemyViewText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(GiuGameConfig::getInstance().configText.bgColor);
    painter->setPen(GiuGameConfig::getInstance().configText.bgColor);
    painter->drawRect(-25,-25, 50, 50);

    painter->setBrush(Qt::red);
    painter->setPen(Qt::red);
    painter->setFont(GiuGameConfig::getInstance().configText.textFont);
    painter->drawText(-10,-10, 20, 20, Qt::AlignCenter, "E");
}
