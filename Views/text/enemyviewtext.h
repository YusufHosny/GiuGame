#ifndef ENEMYVIEWTEXT_H
#define ENEMYVIEWTEXT_H

#include "enemyview2d.h"

class EnemyViewText: public EnemyView2d
{
public:
    EnemyViewText(QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // ENEMYVIEWTEXT_H
