#ifndef TILEVIEWTEXT_H
#define TILEVIEWTEXT_H

#include "itemviewtext.h"

class TileViewText : public ItemViewText {

public:

    TileViewText(int x, int y, float luminance, QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    float luminance;
    int x, y;

};

#endif // TILEVIEWTEXT_H
