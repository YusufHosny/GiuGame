#ifndef HEALTHPACKVIEWTEXT_H
#define HEALTHPACKVIEWTEXT_H

#include "healthpackview2d.h"

class HealthPackViewText : public HealthPackView2d
{
public:

    HealthPackViewText(QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // HEALTHPACKVIEWTEXT_H
