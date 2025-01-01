#ifndef PLAYERVIEW2D_H
#define PLAYERVIEW2D_H

#include "itemview.h"

class PlayerView2D : public ItemView {

public:

    PlayerView2D(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // PLAYERVIEW2D_H
