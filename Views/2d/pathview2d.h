#ifndef PATHVIEW2D_H
#define PATHVIEW2D_H

#include "itemview.h"

class PathView2d : public ItemView
{
private:
    int opacity;

public:
    PathView2d(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PATHVIEW2D_H
