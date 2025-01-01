#ifndef GAMEVIEW2D_H
#define GAMEVIEW2D_H

#include "gameview.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "playerview2d.h"
#include "penemyview2d.h"
#include "enemyview2d.h"
#include "healthpackview2d.h"
#include "levelobject.h"

class GameView2d:  public GameView, public QGraphicsView
{

public:

    GameView2d(QWidget *parent, std::shared_ptr<const GameObject> state);

    void draw(std::shared_ptr<const GameObject> state) override;

private:
    int rows, cols;

    PlayerView2D *playerView;

    QGraphicsRectItem *healthBar;
    QGraphicsRectItem *energyBar;

    void drawPlayer(std::shared_ptr<const LevelObject> levelObject);
    void drawEnemies(std::shared_ptr<const LevelObject> levelObject);
    void drawTiles(std::shared_ptr<const LevelObject> levelObject);
    void drawHealthPacks(std::shared_ptr<const LevelObject> levelObject);
    void drawGui(std::shared_ptr<const LevelObject> levelObject);

    void updateCamera(int zoomStatus, bool reset);

    void wheelEvent(QWheelEvent *e) override;

};



#endif // GAMEVIEW2D_H
