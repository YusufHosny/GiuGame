#include "GameView2d.h"
#include "levelobject.h"
#include "playerview2d.h"
#include "playerobject.h"

GameView2d::GameView2d(QWidget *parent): QGraphicsScene(parent) {

    PlayerView = new PlayerView2D();
    this->addItem(PlayerView);

}

void GameView2d::draw(std::shared_ptr<const GameObject> state) {

    this->clear();

    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(state);
    if (!lo) return;

    for (const auto &tile : lo->getTiles()) {

        float value = tile->getValue();
        int grayScale = static_cast<int>(value * 255);

        QBrush brush(QColor(grayScale, grayScale, grayScale));

        this->addRect(tile->getXPos(), tile->getYPos(), 50, 50, QPen(Qt::black), brush);
    }

    std::shared_ptr<PlayerObject> po = lo -> findChildrenByLabel<PlayerObject>("Player").at(0);

    this->PlayerView->draw(po);

}
