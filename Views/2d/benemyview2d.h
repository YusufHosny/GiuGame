#ifndef BENEMYVIEW2D_H
#define BENEMYVIEW2D_H

#include "itemview.h"

class BEnemyView2D: public ItemView
{

public:

    BEnemyView2D(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // BENEMYVIEW2D_H
