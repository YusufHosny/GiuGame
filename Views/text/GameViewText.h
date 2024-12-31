#ifndef GAMEVIEWTEXT_H
#define GAMEVIEWTEXT_H

#include "gameview.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "playerviewtext.h"
#include "penemyviewtext.h"
#include "enemyviewtext.h"
#include "healthpackviewtext.h"
#include "levelobject.h"

class GameViewText:  public GameView, public QGraphicsView
{

public:

    GameViewText(QWidget *parent, std::shared_ptr<const GameObject> state);

    void draw(std::shared_ptr<const GameObject> state) override;

private:
    int rows, cols;

    PlayerViewText *playerView;
    std::vector<EnemyViewText*> enemyViews;
    std::vector<PEnemyViewText*> penemyViews;
    std::vector<QGraphicsRectItem*> tileViews;
    std::vector<HealthPackViewText*> healthPackViews;

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



#endif // GAMEVIEWTEXT_H
