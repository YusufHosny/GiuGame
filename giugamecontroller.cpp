#include "giugamecontroller.h"
#include "levelobject.h"
#include "gameviewtext.h"
#include "gameview2d.h"
#include "giugameconfig.h"

GiuGameController::GiuGameController(QObject *parent) : GameController(parent) {}

void GiuGameController::init(QWidget* viewparent)  {

    // load first level
    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(gameLoader->load(GiuGameConfig::getInstance().startLevelPath));
    assert(lo);

    this->gameState = lo;

    // create and configure default gameview
    GameView2d* gv2d = new GameView2d(viewparent, lo);
    gv2d->installEventFilter(viewparent); // event filter to reroute events to input manager
    this->views.emplace(ViewType::VIEW2D, gv2d);

    // craete textview
    GameViewText* gvtext = new GameViewText(viewparent, lo);
    gvtext->installEventFilter(viewparent); // event filter to reroute events to input manager
    this->views.emplace(ViewType::VIEWTEXT, gvtext);

    this->currentView = ViewType::VIEW2D;
    this->view = this->views.at(this->currentView);
}

GameView* GiuGameController::changeView() {
    switch(this->currentView) {
    case ViewType::VIEW2D:
        this->currentView = ViewType::VIEWTEXT;
        break;
    case ViewType::VIEWTEXT:
        this->currentView = ViewType::VIEW2D;
        break;
    case ViewType::VIEW3D:
        this->currentView = ViewType::VIEW2D;
        break;
    }

    this->view = this->views.at(this->currentView);
    return this->view;
}
