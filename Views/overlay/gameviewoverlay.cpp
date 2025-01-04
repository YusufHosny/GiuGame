#include "gameviewoverlay.h"
#include "giugameobject.h"

GameViewOverlay::GameViewOverlay(QWidget *parent, std::shared_ptr<const GameObject> state) : GameView2d(parent, state) {

    std::shared_ptr<const GiuGameObject> gState = std::dynamic_pointer_cast<const GiuGameObject>(state);
    std::shared_ptr<LevelObject> levelObject = gState->findChildren<LevelObject>().at(0);
    assert(levelObject); // assert correct type was passed in

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
    this->overlayImage = QPixmap(":/img/testbg.png").scaled(levelObject->getCols()*tileSideLen, levelObject->getRows()*tileSideLen);
}

void GameViewOverlay::drawTiles(std::shared_ptr<const LevelObject> levelObject)
{
    this->scene()->addItem(new QGraphicsPixmapItem(this->overlayImage));
}
