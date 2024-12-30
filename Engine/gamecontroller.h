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
    bool isFrameReady;
    QWaitCondition frameReady;
    QMutex frameLock;

protected:
    GameController() = delete;
    GameController(QObject *parent);

    InputManager* inputManager; // raw pointer, managed by Qt
    GameView* view; // raw pointer, managed by Qt
    std::shared_ptr<GameObject> gameState;
    std::unique_ptr<GameLoader> gameLoader;

public:
    virtual ~GameController() {};

    // setters, returning reference for chaining for convenience
    GameController& setInputManager(InputManager* im);
    GameController& setGameView(GameView* v);
    GameController& setGameState(std::shared_ptr<GameObject> gs);
    GameController& setGameLoader(std::unique_ptr<GameLoader> gl);

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
