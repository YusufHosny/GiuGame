#ifndef GAMEVIEW2D_H
#define GAMEVIEW2D_H

#include "gameview.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "playerview2d.h"

class GameView2d: public GameView, public QGraphicsScene
{

public:

    GameView2d(QWidget *parent);

    void draw(std::shared_ptr<const GameObject> state) override;

private:

    PlayerView2D *PlayerView;

};



#endif // GAMEVIEW2D_H
