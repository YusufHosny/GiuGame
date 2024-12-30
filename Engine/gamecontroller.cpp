#include "gamecontroller.h"
#include <QIntegerForSize>
#include <qdatetime.h>
#include <qthread.h>

GameController::GameController(QObject *parent) : QObject(parent), isFrameReady(true) {}

GameController& GameController::setInputManager(InputManager* im) {
    this->inputManager = im;
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
    this->connect(this, &GameController::sendFrame,
                  this, &GameController::drawFrame);
    // in separate thread
    QThread* loopThread = QThread::create([this]() {
        qint64 tprev = QDateTime::currentMSecsSinceEpoch();

        // initialize the game state
        this->gameState->init_impl();

        // inf loop
        while(true) {
            frameLock.lock();
            while(!isFrameReady)
                frameReady.wait(&frameLock);
            //QThread::usleep(1e6); // 1 SECOND FOR DEBUG

            // retrieve inputs
            std::set<GameInput> inputs = this->inputManager->popInputs();

            // get deltatime
            qint64 tcur = QDateTime::currentMSecsSinceEpoch();
            qint64 deltaTime = tcur - tprev;
            tprev = tcur;

            // step the game state
            this->gameState->step_impl(deltaTime, inputs);

            // draw next frame
            isFrameReady = false;
            emit sendFrame();
            frameLock.unlock();
        }
    });

    loopThread->start();
}

void GameController::drawFrame() {
    frameLock.lock();
    this->view->draw(this->gameState);
    isFrameReady = true;
    frameReady.wakeAll();
    frameLock.unlock();
}
