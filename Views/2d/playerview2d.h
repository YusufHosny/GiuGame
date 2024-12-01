#ifndef GAMEVIEW2DPLAYER_H
#define GAMEVIEW2DPLAYER_H

#include "gameview.h"
#include <QGraphicsItem>



class PlayerView2D : public QGraphicsItem, public GameView {
public:

    PlayerView2D(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    float playerX = 0.0f;
    float playerY = 0.0f;

};

#endif // GAMEVIEW2DPLAYER_H
