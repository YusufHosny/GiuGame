#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include "gameview.h"
#include <QGraphicsItem>


class ItemView : public QGraphicsItem, public GameView {

protected:
    ItemView(QGraphicsItem *parent = nullptr);

public:
    virtual ~ItemView() {};

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

};

#endif // ITEMVIEW_H
