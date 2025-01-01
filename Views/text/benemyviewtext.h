#ifndef BENEMYVIEWTEXT_H
#define BENEMYVIEWTEXT_H

#include "itemviewtext.h"

class BEnemyViewText: public ItemViewText
{

public:

    BEnemyViewText(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // BENEMYVIEWTEXT_H
