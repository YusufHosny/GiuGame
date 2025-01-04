#ifndef DOORVIEWTEXT_H
#define DOORVIEWTEXT_H

#include "doorview2d.h"

class DoorViewText : public DoorView2d
{
public:

    DoorViewText(QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // DOORVIEWTEXT_H
