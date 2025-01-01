#ifndef BENEMYVIEW2D_H
#define BENEMYVIEW2D_H

#include "itemview2d.h"

class BEnemyView2D: public ItemView2d
{

public:

    BEnemyView2D(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // BENEMYVIEW2D_H
