#include "gameview2d.h"

#include "giugameconfig.h"

#include "levelobject.h"
#include "playerobject.h"
#include "pathobject.h"
#include "enemyobject.h"
#include "penemyobject.h"
#include "healthpackobject.h"
#include "benemyobject.h"

#include "itemviewfactory.h"

#include <QWheelEvent>

GameView2d::GameView2d(QWidget* parent, std::shared_ptr<const GameObject> state, ViewType t): QGraphicsView(parent), factory(t) {

    // cast input to a level object
    std::shared_ptr<const LevelObject> levelObject = std::dynamic_pointer_cast<const LevelObject>(state);
    assert(levelObject); // assert correct type was passed in

    // initialize view
    this->init(levelObject);

}

void GameView2d::init(std::shared_ptr<const LevelObject> lo) {
    QGraphicsScene* scene = new QGraphicsScene(this->parent());
    this->setScene(scene);

    this->rows = lo->getRows();
    this->cols = lo->getCols();

    // initialize properties
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(GiuGameConfig::getInstance().gameWidth, GiuGameConfig::getInstance().gameHeight);

}

void GameView2d::drawTiles(std::shared_ptr<const LevelObject> levelObject) {
    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    // get viewport bounds to cull tiles outside of viewport for optimization
    QRectF viewportBounds = this->mapToScene(this->viewport()->geometry()).boundingRect();
    QPointF NW = viewportBounds.topLeft(), SE = viewportBounds.bottomRight();
    // pad edges
    NW = QPointF(
        NW.x()/tileSideLen - 1,
        NW.y()/tileSideLen - 1
    );
    SE = QPointF(
        SE.x()/tileSideLen + 1,
        SE.y()/tileSideLen + 1
    );

    viewportBounds = QRectF(NW, SE);

    for (const auto &tile : levelObject->getTiles()) {
        // check if tile is in viewport bounds and should be drawn, if not skip
        if(!viewportBounds.contains(tile->getXPos(), tile->getYPos())) continue;

        // draw tile
        float value = tile->getValue();
        float luminance = std::isinf(value) ? 0 : value;

        ItemView* t = factory.makeTile(tile->getXPos(), tile->getYPos(), luminance);
        this->scene()->addItem(t);
        t->draw(levelObject);
    }
}

void GameView2d::drawPlayer(std::shared_ptr<const LevelObject> levelObject) {
    std::shared_ptr<PlayerObject> po = levelObject->findChildren<PlayerObject>().at(0);
    playerView = factory.makePlayer();
    this->scene()->addItem(playerView);
    playerView->draw(po);

    // draw player gui
    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
    QGraphicsTextItem* hpLabel = this->scene()->addText(QString::number(po->getProtagonist().getHealth(), 'g', 3));
    hpLabel->setDefaultTextColor(Qt::green);
    hpLabel->setFont(QFont("Arial", 8));
    hpLabel->setPos((po->getProtagonist().getXPos()+.1)*tileSideLen, (po->getProtagonist().getYPos()-.5)*tileSideLen);
    QGraphicsTextItem* energyLabel = this->scene()->addText(QString::number(po->getProtagonist().getEnergy(), 'g', 3));
    energyLabel->setDefaultTextColor(Qt::cyan);
    energyLabel->setFont(QFont("Arial", 8));
    energyLabel->setPos((po->getProtagonist().getXPos()+.1)*tileSideLen, (po->getProtagonist().getYPos()-.9)*tileSideLen);

}

void GameView2d::drawPaths(std::shared_ptr<const LevelObject> levelObject)
{
    std::shared_ptr<PlayerObject> po = levelObject->findChildren<PlayerObject>().at(0);
    std::vector<std::shared_ptr<PathObject>> paths = po->findChildren<PathObject>();
    for(const auto& path : paths) {
        ItemView* pathView = factory.makePath();
        this->scene()->addItem(pathView);
        pathView->draw(path);
    }
}

void GameView2d::drawEnemies(std::shared_ptr<const LevelObject> levelObject ) {
    // draw enemies
    std::vector<std::shared_ptr<EnemyObject>> enemies = levelObject->findChildren<EnemyObject>();
    for (const auto &enemy : enemies) {
        ItemView* ev = factory.makeEnemy();
        this->scene()->addItem(ev);
        ev->draw(enemy);
    }

    // draw penemies
    std::vector<std::shared_ptr<PEnemyObject>> penemies = levelObject->findChildren<PEnemyObject>();
    for (const auto &penemy : penemies) {
        ItemView* pev = factory.makePEnemy();
        this->scene()->addItem(pev);
        pev->draw(penemy);
    }

    // draw benemies
    std::vector<std::shared_ptr<BEnemyObject>> benemies = levelObject->findChildren<BEnemyObject>();
    for (const auto &benemy : benemies) {
        ItemView* bev = factory.makeBEnemy();
        this->scene()->addItem(bev);
        bev->draw(benemy);
    }
}

void GameView2d::drawHealthPacks(std::shared_ptr<const LevelObject> levelObject ) {
    std::vector<std::shared_ptr<HealthPackObject>> healthPacks = levelObject->findChildren<HealthPackObject>();
    for (const auto &hp : healthPacks) {
        ItemView* hpv = factory.makeHealthPack();
        this->scene()->addItem(hpv);
        hpv->draw(hp);
    }
}

void GameView2d::wheelEvent(QWheelEvent* e) { e->ignore(); }; // ignore wheel event, just to be safe

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
    this->drawPaths(levelObject);
    this->drawEnemies(levelObject);
    this->drawHealthPacks(levelObject);
    this->drawPlayer(levelObject);

    this->updateCamera(levelObject->getZoomStatus(), levelObject->getCameraReset());

}
