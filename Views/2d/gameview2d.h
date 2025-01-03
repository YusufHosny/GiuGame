#ifndef GAMEVIEW2D_H
#define GAMEVIEW2D_H

#include "gameview.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "levelobject.h"
#include "itemview.h"
#include "itemviewfactory.h"

class GameView2d: public QGraphicsView, public GameView
{

public:

    GameView2d(QWidget* parent, std::shared_ptr<const GameObject> state, ViewType t = ViewType::VIEW2D);

    void init(std::shared_ptr<const LevelObject>);

    void draw(std::shared_ptr<const GameObject> state) override;

protected:
    ItemViewFactory factory;

private:
    int rows, cols;

    ItemView* playerView;

    virtual void drawPlayer(std::shared_ptr<const LevelObject> levelObject);
    virtual void drawPaths(std::shared_ptr<const LevelObject> levelObject);
    virtual void drawEnemies(std::shared_ptr<const LevelObject> levelObject);
    virtual void drawTiles(std::shared_ptr<const LevelObject> levelObject);
    virtual void drawHealthPacks(std::shared_ptr<const LevelObject> levelObject);
    virtual void drawGui(std::shared_ptr<const LevelObject> levelObject);

    virtual void updateCamera(int zoomStatus, bool reset);

    void wheelEvent(QWheelEvent* e) override;

};



#endif // GAMEVIEW2D_H