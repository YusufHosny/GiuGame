#ifndef GAMEVIEW2D_H
#define GAMEVIEW2D_H

#include "gameview.h"
#include <QGraphicsScene>
#include <QGraphicsView>

class GameView2d: public GameView, public QGraphicsScene
{


public:

    GameView2d(QWidget *parent);

    void draw(std::shared_ptr<const GameObject> state) override;

private:

    QGraphicsView *view2D;
};



#endif // GAMEVIEW2D_H
