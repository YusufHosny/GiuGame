#ifndef PLAYERVIEW2D_H
#define PLAYERVIEW2D_H

#include "itemview.h"

class PlayerView2d : public ItemView {

public:

    PlayerView2d(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    static std::map<unsigned int,  std::vector<QPixmap>> sprites;
    unsigned int animationState;
    unsigned int frameId;

    static void loadSprites();

};

#endif // PLAYERVIEW2D_H
