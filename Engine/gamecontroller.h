#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <memory>
#include "inputmanager.h"
#include "gameloader.h"
#include "gameview.h"
#include "QGraphicsView"

class GameController: public QObject
{
    Q_OBJECT

protected:
    GameController();

    std::unique_ptr<InputManager> inputManager;
    std::shared_ptr<GameObject> gameState;
    std::unique_ptr<GameLoader> gameLoader;
    GameView* view; // raw pointer, GameView lifetime managed by Qt

public:
    // setters, returning reference for chaining for convenience
    GameController& setInputManager(std::unique_ptr<InputManager> im);
    GameController& setGameState(std::shared_ptr<GameObject> gs);
    GameController& setGameLoader(std::unique_ptr<GameLoader> gl);
    GameController& setGameView(GameView* v);

    // scene getter, for visualization
    QGraphicsView* getView();

    // start game loop
    void start();

};

#endif // GAMECONTROLLER_H
