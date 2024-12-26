#ifndef PENEMYVIEW2D_H
#define PENEMYVIEW2D_H

#include "itemview2d.h"

class PEnemyView2D: public ItemView2d
{
public:
    PEnemyView2D(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PENEMYVIEW2D_H
