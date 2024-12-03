#ifndef PLAYERVIEW2D_H
#define PLAYERVIEW2D_H

#include <QGraphicsItem>
#include "characterview2d.h"



class PlayerView2D : public CharacterView2D {

public:

    PlayerView2D(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // PLAYERVIEW2D_H
