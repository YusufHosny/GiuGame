#ifndef GAMEVIEW3D_H
#define GAMEVIEW3D_H

#include "gameview.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "levelobject.h"
#include "itemview.h"
#include "itemviewfactory.h"

class GameView3d: public QGraphicsView, public GameView
{

public:

    GameView3d(QWidget* parent, std::shared_ptr<const GameObject> state, ViewType t = ViewType::VIEW3D);

    void init(std::shared_ptr<const LevelObject>);

    int getCols() const;

    void draw(std::shared_ptr<const GameObject> state) override;

private:
    ItemViewFactory factory;

    int rows, cols;

    ItemView* playerView;

    // rotate to direction and translate rect to camera space
    QRectF toCameraSpace(QRectF in, QPointF camera, Direction cameraFacing);

    // translate rect in 2d camera space to a 2d polygon in 3d screen space by applying perspective
    // upright bool decides if this rect is drawn upright or flat on the ground
    QPolygonF toScreenSpace(QRectF in, bool upright, QPointF camera, Direction cameraFacing);

    // frustrum culling
    bool isCulled(QRectF in, QPointF camera, Direction cameraFacing);

    std::array<float, 1*4> matmul(std::array<float, 1*4> a, std::array<float, 4*4> b);

    virtual void drawTiles(std::shared_ptr<const LevelObject> levelObject);
    virtual void drawPaths(std::shared_ptr<const LevelObject> levelObject);
    virtual void drawEnemies(std::shared_ptr<const LevelObject> levelObject);
    virtual void drawItems(std::shared_ptr<const LevelObject> levelObject);

    void wheelEvent(QWheelEvent* e) override;

};



#endif // GAMEVIEW3D_H
