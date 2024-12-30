#include "GameView2d.h"
#include "levelobject.h"
#include "playerview2d.h"
#include "playerobject.h"
#include "enemyview2d.h"
#include "enemyobject.h"
#include "penemyobject.h"
#include "penemyview2d.h"
#include "healthpackobject.h"
#include "healthpackview2d.h"
#include "giugameconfig.h"
#include <QWheelEvent>

GameView2d::GameView2d(QWidget *parent, std::shared_ptr<const GameObject> state): QGraphicsView(parent) {

    // cast input to a level object
    std::shared_ptr<const LevelObject> levelObject = std::dynamic_pointer_cast<const LevelObject>(state);
    assert(levelObject); // assert correct type was passed in

    QGraphicsScene* scene = new QGraphicsScene(parent);
    this->setScene(scene);

    this->rows = levelObject->getRows();
    this->cols = levelObject->getCols();

    // initialize properties
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(GiuGameConfig::getInstance().gameWidth, GiuGameConfig::getInstance().gameHeight);

    // draw all items
    this->drawTiles(levelObject);
    this->drawPlayer(levelObject);
    this->drawEnemies(levelObject);
    this->drawHealthPacks(levelObject);
    this->drawGui(levelObject);

    // center on player
    this->centerOn(playerView);

}

void GameView2d::drawTiles(std::shared_ptr<const LevelObject> levelObject ) {
    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    // get viewport bounds to cull tiles outside of viewport for optimization
    QRectF viewportBounds = this->mapToScene(this->viewport()->geometry()).boundingRect();
    QPointF NW = viewportBounds.topLeft(), SE = viewportBounds.bottomRight();
    NW /= tileSideLen;
    SE /= tileSideLen;
    viewportBounds = QRectF(NW, SE);

    for (const auto &tile : levelObject->getTiles()) {
        // check if tile is in viewport bounds and should be drawn, if not skip
        if(!viewportBounds.contains(tile->getXPos(), tile->getYPos())) continue;

        // draw tile
        float value = tile->getValue();
        int grayScale = static_cast<int>( (std::isinf(value) ? 0 : value) * 255);
        QBrush brush(QColor(grayScale, grayScale, grayScale));
        auto rectItem = this->scene()->addRect(tile->getXPos() * tileSideLen, tile->getYPos() * tileSideLen, tileSideLen, tileSideLen, QPen(Qt::NoPen), brush);
        tileViews.push_back(rectItem);
    }
}

void GameView2d::drawPlayer(std::shared_ptr<const LevelObject> levelObject ) {
    std::shared_ptr<PlayerObject> po = levelObject->findChildren<PlayerObject>().at(0);
    playerView = new PlayerView2D();
    this->scene()->addItem(playerView);
    playerView->draw(po);
}

void GameView2d::drawEnemies(std::shared_ptr<const LevelObject> levelObject ) {
    // draw enemies
    std::vector<std::shared_ptr<EnemyObject>> enemies = levelObject->findChildren<EnemyObject>();
    for (const auto &enemy : enemies) {
        EnemyView2D *ev = new EnemyView2D();
        this->scene()->addItem(ev);
        enemyViews.push_back(ev);
        ev->draw(enemy);
    }

    // draw penemies
    std::vector<std::shared_ptr<PEnemyObject>> penemies = levelObject->findChildren<PEnemyObject>();
    for (const auto &penemy : penemies) {
        PEnemyView2D *pev = new PEnemyView2D();
        this->scene()->addItem(pev);
        penemyViews.push_back(pev);
        pev->draw(penemy);
    }

    // TODO draw xenemies
}

void GameView2d::drawHealthPacks(std::shared_ptr<const LevelObject> levelObject ) {
    std::vector<std::shared_ptr<HealthPackObject>> healthPacks = levelObject->findChildren<HealthPackObject>();
    for (const auto &hp : healthPacks) {
        HealthPackView2D *hpv = new HealthPackView2D();
        this->scene()->addItem(hpv);
        healthPackViews.push_back(hpv);
        hpv->draw(hp);
    }
}

void GameView2d::drawGui(std::shared_ptr<const LevelObject> levelObject ) {
    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    int barWidth = tileSideLen;
    int leftMargin = (this->rows + 2) * tileSideLen;
    int topOffset = 2 * tileSideLen;

    int maxBarHeight = 200;
    float playerEnergy = levelObject->findChildren<PlayerObject>().at(0)->getProtagonist().getEnergy() / 100;
    float playerHealth = levelObject->findChildren<PlayerObject>().at(0)->getProtagonist().getHealth() / 100;

    healthBar = this->scene()->addRect(leftMargin, topOffset, barWidth, maxBarHeight * playerHealth, QPen(Qt::NoPen), QBrush(Qt::green));
    energyBar = this->scene()->addRect(leftMargin + 2*tileSideLen, topOffset, barWidth, maxBarHeight * playerEnergy, QPen(Qt::NoPen), QBrush(Qt::green));

    QGraphicsTextItem *hpLabel = this->scene()->addText("Health");
    hpLabel->setDefaultTextColor(Qt::white);
    hpLabel->setFont(QFont("Arial", 12));
    hpLabel->setPos(leftMargin + (tileSideLen/5), topOffset + maxBarHeight + (tileSideLen/5));

    QGraphicsTextItem *energyLabel = this->scene()->addText("Energy");
    energyLabel->setDefaultTextColor(Qt::white);
    energyLabel->setFont(QFont("Arial", 12));
    energyLabel->setPos(leftMargin + 2*tileSideLen - tileSideLen/5, topOffset + maxBarHeight + (tileSideLen/5));
}

void GameView2d::wheelEvent(QWheelEvent *e) { e->ignore(); }; // ignore wheel event, just to be safe

void GameView2d::updateCamera(int zoomStatus, bool reset) {
    // zoom in out
    float zoomSpeed = GiuGameConfig::getInstance().config2d.zoomSpeed;

    this->setResizeAnchor(AnchorUnderMouse);
    this->setTransformationAnchor(AnchorUnderMouse);
    if(zoomStatus == 1 && this->transform().m11() > 0.3) {
        this->scale(0.9 * zoomSpeed, 0.9 * zoomSpeed);
    }
    else if(zoomStatus == -1 && this->transform().m11() < 3) {
        this->scale(1.1 * zoomSpeed, 1.1 * zoomSpeed);
    }

    if(reset) {
        this->centerOn(playerView);
    }
}

void GameView2d::draw(std::shared_ptr<const GameObject> state) {

    std::shared_ptr<const LevelObject> levelObject = std::dynamic_pointer_cast<const LevelObject>(state);
    assert(levelObject); // assert correct type was passed in

    this->scene()->clear();

    this->drawTiles(levelObject);
    this->drawPlayer(levelObject);
    this->drawEnemies(levelObject);
    this->drawHealthPacks(levelObject);
    this->drawGui(levelObject);

    this->updateCamera(levelObject->getZoomStatus(), levelObject->getCameraReset());

}

