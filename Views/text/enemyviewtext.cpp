#include "enemyviewtext.h"
#include "giugameconfig.h"
#include <QPainter>

EnemyViewText::EnemyViewText(QGraphicsItem *parent) : EnemyView2d(parent)  {}


void EnemyViewText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(GiuGameConfig::getInstance().configText.bgColor);
    painter->setPen(GiuGameConfig::getInstance().configText.bgColor);
    painter->drawRect(this->boundingRect());

    painter->setBrush(Qt::red);
    painter->setPen(Qt::red);
    painter->setFont(GiuGameConfig::getInstance().configText.textFont);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, "E");
}
