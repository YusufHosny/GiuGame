#include "GameView2d.h"

GameView2d::GameView2d(QWidget *parent): QGraphicsScene(parent), view2D( new QGraphicsView(this, parent)) {

    // Matching size of scene with size of window
    view2D->resize(parent->size());
}

void GameView2d::draw(std::shared_ptr<const GameObject> state) {



}
