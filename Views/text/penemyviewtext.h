#ifndef PENEMYVIEWTEXT_H
#define PENEMYVIEWTEXT_H

#include "itemviewtext.h"

class PEnemyViewText: public ItemViewText
{
public:
    PEnemyViewText(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PENEMYVIEWTEXT_H
