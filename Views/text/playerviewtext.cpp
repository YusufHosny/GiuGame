#include "playerviewtext.h"
#include "giugameconfig.h"
#include <QPainter>

PlayerViewText::PlayerViewText(QGraphicsItem *parent) : PlayerView2D(parent)  {}

void PlayerViewText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(GiuGameConfig::getInstance().configText.bgColor);
    painter->setPen(GiuGameConfig::getInstance().configText.bgColor);
    painter->drawRect(this->boundingRect());

    painter->setBrush(Qt::blue);
    painter->setPen(Qt::blue);
    painter->setFont(GiuGameConfig::getInstance().configText.textFont);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, "P");
}
