#ifndef PLAYERVIEWTEXT_H
#define PLAYERVIEWTEXT_H

#include <QGraphicsItem>
#include "itemviewtext.h"



class PlayerViewText : public ItemViewText {

public:

    PlayerViewText(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // PLAYERVIEWTEXT_H
