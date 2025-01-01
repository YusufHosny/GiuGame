#ifndef TILEVIEWTEXT_H
#define TILEVIEWTEXT_H

#include "tileview2d.h"

class TileViewText : public TileView2d {

public:

    TileViewText(int x, int y, float luminance, QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // TILEVIEWTEXT_H
