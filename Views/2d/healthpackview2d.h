#ifndef HEALTHPACKVIEW2D_H
#define HEALTHPACKVIEW2D_H


#include <QGraphicsItem>
#include "characterview2d.h"

class HealthPackView2D : public CharacterView2D {
public:

    HealthPackView2D(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    float X = 0.0f;
    float Y = 0.0f;

};

#endif // HEALTHPACKVIEW2D_H
