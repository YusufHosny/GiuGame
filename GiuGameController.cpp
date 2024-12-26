#include "GiuGameController.h"
#include "levelobject.h"
#include "GameView2d.h"

GiuGameController::GiuGameController() : GameController() {}

void GiuGameController::init(MainWindow* parent)  {

    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(gameLoader->load(":img/maze1.png"));
    assert(lo);

    view = new GameView2d(parent, lo);

}

QGraphicsScene* GiuGameController::getScene() {
    return dynamic_cast<QGraphicsScene*>(view);
}
