#ifndef GIUGAMECONTROLLER_H
#define GIUGAMECONTROLLER_H

#include "gamecontroller.h"
#include "giugameconfig.h"

class GiuGameController : public GameController
{
    Q_OBJECT

public:
    GiuGameController() = delete;
    GiuGameController(QObject* parent);

    void init(QWidget* parent);

    GameView* changeView();

private:
    std::map<ViewType, GameView*> views;
    ViewType currentView;
};


#endif // GIUGAMECONTROLLER_H
