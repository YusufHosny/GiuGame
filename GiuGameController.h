#ifndef GIUGAMECONTROLLER_H
#define GIUGAMECONTROLLER_H

#include "gamecontroller.h"

class GiuGameController : public GameController
{
    Q_OBJECT

public:
    GiuGameController() = delete;
    GiuGameController(QObject* parent);

    void init(QWidget* parent);

};


#endif // GIUGAMECONTROLLER_H
