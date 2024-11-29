#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <memory>
#include "inputmanager.h"
#include "gameloader.h"
#include "gameview.h"

class GameController: public QObject
{
    Q_OBJECT

protected:
    std::unique_ptr<InputManager> inputManager;
    std::shared_ptr<GameObject> gameState;
    std::unique_ptr<GameLoader> gameLoader;
    std::shared_ptr<GameView> view;

public:
    GameController();

    // initialize loader and load initial state
    virtual void init() = 0;

    // start game loop
    void start();

};

#endif // GAMECONTROLLER_H
