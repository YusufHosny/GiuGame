#ifndef PENEMYVIEWTEXT_H
#define PENEMYVIEWTEXT_H

#include "penemyview2d.h"

class PEnemyViewText: public PEnemyView2D
{
public:
    PEnemyViewText(QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PENEMYVIEWTEXT_H
