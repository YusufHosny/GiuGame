#ifndef GIUGAMECONTROLLER_H
#define GIUGAMECONTROLLER_H

#include "gamecontroller.h"
#include "mainwindow.h"

class GiuGameController : public GameController
{
    Q_OBJECT

private:
    GameView* view;

public:
    GiuGameController();

    void init(MainWindow* parent);

};


#endif // GIUGAMECONTROLLER_H
