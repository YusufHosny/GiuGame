#include "gamecontroller.h"
#include <set>
#include <QIntegerForSize>
#include <qdatetime.h>

GameController::GameController() {
    // initialize world loader
    this->worldLoader = WorldLoader();

}



void GameController::start()
{
    // load correct start level
    this->gameState = this->worldLoader.load("TODO PATH");

    qint64 tprev = QDateTime::currentMSecsSinceEpoch();

    // initialize all children
    this->gameState->init();


    // infinite loop
    while(true) {
        // retrieve inputs
        std::set<GameInput> inputs = this->inputManager->popInputs();

        // process state altering inputs
        if( inputs.find(GameInput::PAUSE) != inputs.end() ) {

        }

        else if( inputs.find(GameInput::GOTOMENU) != inputs.end() ) {

        }

        if( inputs.find(GameInput::SWITCHVIEW2D) != inputs.end() ) {

        }

        else if( inputs.find(GameInput::SWITCHVIEW3D) != inputs.end() ) {

        }

        else if( inputs.find(GameInput::SWITCHVIEWTEXT) != inputs.end() ) {

        }


        // get deltatime
        qint64 tcur = QDateTime::currentMSecsSinceEpoch();
        qint64 deltaTime = tcur - tprev;
        tprev = tcur;


        // update all children
        this->gameState->step(deltaTime, inputs);

        // draw next frame
        this->view->draw(this->gameState);
    }
}
