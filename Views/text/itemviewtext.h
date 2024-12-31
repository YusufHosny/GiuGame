#ifndef ITEMVIEWTEXT_H
#define ITEMVIEWTEXT_H

#include "gameview.h"
#include <QGraphicsItem>


class ItemViewText : public QGraphicsItem, public GameView {
public:

    ItemViewText(QGraphicsItem *parent = nullptr): QGraphicsItem(parent){};

    virtual void draw(std::shared_ptr<const GameObject> go) override = 0;

    virtual QRectF boundingRect() const override = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

protected:
    float X = 0.0f;
    float Y = 0.0f;

};

#endif // ITEMVIEWTEXT_H
