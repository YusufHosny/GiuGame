#include "giugamecontroller.h"
#include "gameviewtext.h"
#include "gameview2d.h"
#include "gameviewoverlay.h"
#include "gameview3d.h"
#include "giugameconfig.h"
#include "giugameobject.h"

GiuGameController::GiuGameController(QObject *parent) : GameController(parent) {}

void GiuGameController::init(QWidget* viewparent)  {

    // load first level
    std::shared_ptr<GiuGameObject> baseState = std::make_shared<GiuGameObject>();
    baseState->addChild(gameLoader->load(GiuGameConfig::getInstance().startLevel));

    this->gameState = baseState;

    // create and configure default gameview
    GameView2d* gv2d = new GameView2d(viewparent, this->gameState);
    gv2d->installEventFilter(viewparent); // event filter to reroute events to input manager
    this->views.emplace(ViewType::VIEW2D, gv2d);

    // craete textview
    GameViewText* gvtext = new GameViewText(viewparent, this->gameState);
    gvtext->installEventFilter(viewparent); // event filter to reroute events to input manager
    this->views.emplace(ViewType::VIEWTEXT, gvtext);

    // craete overlayview
    GameViewOverlay* goverlay = new GameViewOverlay(viewparent, this->gameState);
    goverlay->installEventFilter(viewparent); // event filter to reroute events to input manager
    this->views.emplace(ViewType::VIEWOVERLAY, goverlay);

    // create 3d view
    GameView3d* gv3d = new GameView3d(viewparent, this->gameState);
    gv3d->installEventFilter(viewparent); // event filter to reroute events to input manager
    this->views.emplace(ViewType::VIEW3D, gv3d);

    this->currentView = ViewType::VIEW3D;
    this->view = this->views.at(this->currentView);
}

GameView* GiuGameController::changeView() {
    switch(this->currentView) {
    case ViewType::VIEW2D:
        this->currentView = ViewType::VIEWTEXT;
        break;
    case ViewType::VIEWTEXT:
        this->currentView = ViewType::VIEWOVERLAY;
        break;
    case ViewType::VIEWOVERLAY:
        this->currentView = ViewType::VIEW3D;
        break;
    case ViewType::VIEW3D:
        this->currentView = ViewType::VIEW2D;
        break;
    }

    this->view = this->views.at(this->currentView);
    return this->view;
}
