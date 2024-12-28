#include "GiuGameController.h"
#include "levelobject.h"
#include "GameView2d.h"

GiuGameController::GiuGameController() : GameController() {}

void GiuGameController::init(MainWindow* parent)  {

    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(gameLoader->load(":img/worldmap.png"));
    assert(lo);

    this->gameState = lo;

    view = new GameView2d(parent, lo);
}
