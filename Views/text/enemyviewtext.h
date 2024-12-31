#ifndef ENEMYVIEWTEXT_H
#define ENEMYVIEWTEXT_H

#include "itemviewtext.h"

class EnemyViewText: public ItemViewText
{

public:

    EnemyViewText(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // ENEMYVIEWTEXT_H
