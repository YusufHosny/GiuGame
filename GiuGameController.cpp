#include "GiuGameController.h"
#include "levelobject.h"
#include "GameView2d.h"
#include "giugameconfig.h"

GiuGameController::GiuGameController(QObject *parent) : GameController(parent) {}

void GiuGameController::init(QWidget* viewparent)  {

    // load first level
    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(gameLoader->load(":img/worldmap.png"));
    assert(lo);

    //
    this->gameState = lo;

    // create and configure default gameview
    auto gv = new GameView2d(viewparent, lo);
    gv->installEventFilter(viewparent);

    view = gv;
}
