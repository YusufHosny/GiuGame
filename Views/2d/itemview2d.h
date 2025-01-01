#ifndef ITEMVIEW2D_H
#define ITEMVIEW2D_H

#include "gameview.h"
#include <QGraphicsItem>


class ItemView2d : public QGraphicsItem, public GameView {
public:

    ItemView2d(QGraphicsItem *parent = nullptr): QGraphicsItem(parent){};

    virtual QRectF boundingRect() const override = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

protected:
    float X = 0.0f;
    float Y = 0.0f;

};

#endif // ITEMVIEW2D_H
