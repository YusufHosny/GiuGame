#ifndef HEALTHPACKVIEW2D_H
#define HEALTHPACKVIEW2D_H

#include "itemview.h"

class HealthPackView2d : public ItemView {
public:

    HealthPackView2d(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // HEALTHPACKVIEW2D_H
