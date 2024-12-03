#ifndef CHARACTERVIEW2D_H
#define CHARACTERVIEW2D_H

#include "gameview.h"
#include <QGraphicsItem>


class CharacterView2D : public QGraphicsItem, public GameView {
public:

    CharacterView2D(QGraphicsItem *parent = nullptr): QGraphicsItem(parent){};

    virtual void draw(std::shared_ptr<const GameObject> go) override = 0;

    virtual QRectF boundingRect() const override = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

protected:
    float X = 0.0f;
    float Y = 0.0f;

};

#endif // CHARACTERVIEW2D_H
