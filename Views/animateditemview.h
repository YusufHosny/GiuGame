#ifndef ANIMATEDITEMVIEW_H
#define ANIMATEDITEMVIEW_H

#include "itemview.h"

class AnimatedItemView : public ItemView
{
public:
    AnimatedItemView(QGraphicsItem *parent);

    virtual ~AnimatedItemView() {};

protected:
    unsigned int animationState;
    unsigned int frameId;

    virtual std::map<unsigned int,  std::vector<QPixmap>>& getSprites() = 0;
    virtual void loadSprites() = 0;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // ANIMATEDITEMVIEW_H
