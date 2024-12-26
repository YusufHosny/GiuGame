#ifndef ENEMYVIEW2D_H
#define ENEMYVIEW2D_H

#include "itemview2d.h"

class EnemyView2D: public ItemView2d
{

public:

    EnemyView2D(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // ENEMYVIEW2D_H
