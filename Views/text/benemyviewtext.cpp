#include "benemyviewtext.h"
#include "giugameconfig.h"

#include <QPainter>

BEnemyViewText::BEnemyViewText(QGraphicsItem *parent) : BEnemyView2d(parent)  {}

void BEnemyViewText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(GiuGameConfig::getInstance().configText.bgColor);
    painter->setPen(GiuGameConfig::getInstance().configText.bgColor);
    painter->drawRect(this->boundingRect());

    painter->setBrush(Qt::red);
    painter->setPen(Qt::red);
    painter->setFont(GiuGameConfig::getInstance().configText.textFont);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, "B");
}
