#ifndef GAMEVIEW2D_H
#define GAMEVIEW2D_H

#include "gameview.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "playerview2d.h"
#include "penemyview2d.h"
#include "enemyview2d.h"
#include "healthpackview2d.h"

class GameView2d: public GameView, public QGraphicsScene
{

public:

    GameView2d(QWidget *parent, std::shared_ptr<const GameObject> state);

    void draw(std::shared_ptr<const GameObject> state) override;

private:

    PlayerView2D *playerView;
    std::vector<EnemyView2D *> enemyViews;
    std::vector<PEnemyView2D *> penemyViews;
    std::vector<QGraphicsRectItem *> tileViews;
    std::vector<HealthPackView2D *> healthPackViews;

    int rows, cols;

    QGraphicsRectItem *healthBar;
    QGraphicsRectItem *energyBar;

};



#endif // GAMEVIEW2D_H
