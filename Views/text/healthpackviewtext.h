#ifndef HEALTHPACKVIEWTEXT_H
#define HEALTHPACKVIEWTEXT_H


#include <QGraphicsItem>
#include "itemviewtext.h"

class HealthPackViewText : public ItemViewText {
public:

    HealthPackViewText(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    float X = 0.0f;
    float Y = 0.0f;

};

#endif // HEALTHPACKVIEWTEXT_H
