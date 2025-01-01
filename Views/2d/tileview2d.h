#ifndef TILEVIEW2D_H
#define TILEVIEW2D_H

#include "itemview.h"

class TileView2d : public ItemView {

public:
    TileView2d(int x, int y, float luminance, QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:

    float luminance;
    int x, y;

};

#endif // TILEVIEW2D_H
