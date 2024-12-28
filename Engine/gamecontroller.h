#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <QGraphicsView>
#include <memory>
#include "inputmanager.h"
#include "gameloader.h"
#include "gameview.h"

class GameController: public QObject
{
    Q_OBJECT

private:
    QWaitCondition frameReady;
    QMutex frameLock;
    int maxFrameRate = 200;

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

public slots:
    void drawFrame();

signals:
    void sendFrame();
};

#endif // GAMECONTROLLER_H
