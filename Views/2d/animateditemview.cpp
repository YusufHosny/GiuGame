#include "animateditemview.h"
#include <QPainter>

AnimatedItemView::AnimatedItemView(QGraphicsItem *parent) : ItemView(parent) {};

void AnimatedItemView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(this->boundingRect().toRect(), this->getSprites().at(this->animationState).at(this->frameId));
}
