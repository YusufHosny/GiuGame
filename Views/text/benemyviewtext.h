#ifndef BENEMYVIEWTEXT_H
#define BENEMYVIEWTEXT_H

#include "benemyview2d.h"

class BEnemyViewText: public BEnemyView2d
{
public:

    BEnemyViewText(QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BENEMYVIEWTEXT_H
