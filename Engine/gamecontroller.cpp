#include "gamecontroller.h"
#include <set>
#include <QIntegerForSize>
#include <qdatetime.h>
#include <qthread.h>

GameController::GameController() {}

GameController& GameController::setInputManager(std::unique_ptr<InputManager> im) {
    this->inputManager = std::move(im);
    return *this;
}

GameController& GameController::setGameState(std::shared_ptr<GameObject> gs) {
    this->gameState = gs;
    return *this;
}

GameController& GameController::setGameLoader(std::unique_ptr<GameLoader> gl) {
    this->gameLoader = std::move(gl);
    return *this;
}

GameController& GameController::setGameView(GameView* v) {
    this->view = v;
    return *this;
}

QGraphicsView* GameController::getView() {
    return dynamic_cast<QGraphicsView*>(this->view);
}

void GameController::start()
{
    // in separate thread
    QThread* loopThread = QThread::create([this]() {
        qint64 tprev = QDateTime::currentMSecsSinceEpoch();

        // initialize the game state
        this->gameState->init_impl();

        // inf loop
        while(true) {
            // retrieve inputs
            std::set<GameInput> inputs = this->inputManager->popInputs();

            // get deltatime
            qint64 tcur = QDateTime::currentMSecsSinceEpoch();
            qint64 deltaTime = tcur - tprev;
            tprev = tcur;

            // step the game state
            this->gameState->step_impl(deltaTime, inputs);

            // draw next frame
            this->view->draw(this->gameState);
        }
    });

    loopThread->start();
}
