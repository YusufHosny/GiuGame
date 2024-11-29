#include "gamecontroller.h"
#include <set>
#include <QIntegerForSize>
#include <qdatetime.h>
#include <qthread.h>

GameController::GameController() {}


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
