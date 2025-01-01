#include "penemyviewtext.h"
#include "giugameconfig.h"
#include <QPainter>

PEnemyViewText::PEnemyViewText(QGraphicsItem *parent) : PEnemyView2d(parent)  {}

void PEnemyViewText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(GiuGameConfig::getInstance().configText.bgColor);
    painter->setPen(GiuGameConfig::getInstance().configText.bgColor);
    painter->drawRect(this->boundingRect());

    painter->setBrush(QColorConstants::Svg::purple);
    painter->setPen(QColorConstants::Svg::purple);
    painter->setFont(GiuGameConfig::getInstance().configText.textFont);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, "V");
}
