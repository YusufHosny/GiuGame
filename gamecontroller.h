#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <memory>
#include "inputmanager.h"
#include "levelobject.h"
#include "worldloader.h"
#include "gameview.h"

class GameController: public QObject
{
    Q_OBJECT

private:
    std::unique_ptr<InputManager> inputManager;

    std::shared_ptr<LevelObject> gameState;

    WorldLoader worldLoader;

    std::shared_ptr<GameView> view;



    // TODO View Object attribute

public:
    GameController();

    void start();

};

#endif // GAMECONTROLLER_H
