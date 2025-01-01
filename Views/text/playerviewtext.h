#ifndef PLAYERVIEWTEXT_H
#define PLAYERVIEWTEXT_H

#include "playerview2d.h"

class PlayerViewText : public PlayerView2d
{
public:
    PlayerViewText(QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // PLAYERVIEWTEXT_H
