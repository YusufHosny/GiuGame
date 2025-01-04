#include "doorviewtext.h"
#include "giugameconfig.h"
#include <QPainter>

DoorViewText::DoorViewText(QGraphicsItem *parent) : DoorView2d(parent)  {}

void DoorViewText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(GiuGameConfig::getInstance().configText.bgColor);
    painter->setPen(GiuGameConfig::getInstance().configText.bgColor);
    painter->drawRect(this->boundingRect());

    painter->setBrush(Qt::yellow);
    painter->setPen(Qt::yellow);
    painter->setFont(GiuGameConfig::getInstance().configText.textFont);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, "D");
}
