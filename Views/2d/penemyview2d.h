#ifndef PENEMYVIEW2D_H
#define PENEMYVIEW2D_H

#include "itemview.h"

class PEnemyView2D: public ItemView
{
public:
    PEnemyView2D(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PENEMYVIEW2D_H
