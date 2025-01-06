#include "gameview3d.h"

#include "giugameconfig.h"

#include "levelobject.h"
#include "playerobject.h"
#include "pathobject.h"
#include "enemyobject.h"
#include "penemyobject.h"
#include "healthpackobject.h"
#include "benemyobject.h"
#include "giugameobject.h"
#include "doorobject.h"

#include "itemviewfactory.h"

#include <QWheelEvent>

GameView3d::GameView3d(QWidget* parent, std::shared_ptr<const GameObject> state, ViewType t): QGraphicsView(parent), factory(t) {

    std::shared_ptr<const GiuGameObject> gState = std::dynamic_pointer_cast<const GiuGameObject>(state);
    std::shared_ptr<LevelObject> levelObject = gState->findChildren<LevelObject>().at(0);
    assert(levelObject); // assert correct type was passed in

    // initialize view
    this->init(levelObject);

}

void GameView3d::init(std::shared_ptr<const LevelObject> lo) {
    QGraphicsScene* scene = new QGraphicsScene(this->parent());
    this->setScene(scene);

    this->rows = lo->getRows();
    this->cols = lo->getCols();

    // initialize properties
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(GiuGameConfig::getInstance().gameWidth, GiuGameConfig::getInstance().gameHeight);

    this->setSceneRect(QRectF(0, 0, GiuGameConfig::getInstance().gameWidth, GiuGameConfig::getInstance().gameHeight));

}

int GameView3d::getCols() const {
    return this->cols;
}

void GameView3d::drawTiles(std::shared_ptr<const LevelObject> levelObject) {
    // camera info
    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
    auto player = levelObject->findChildren<PlayerObject>().at(0);
    QPointF camera = QPoint(player->getTile().getXPos()*tileSideLen, player->getTile().getYPos()*tileSideLen);
    Direction cameraFacing = player->getFacing();

    for (const auto &tile : levelObject->getTiles()) {
        // check for frustrum culling
        auto tilerect = QRectF(tile->getXPos()*tileSideLen, tile->getYPos()*tileSideLen, tileSideLen, tileSideLen);
        if(this->isCulled(tilerect, camera, cameraFacing)) continue;

        // draw tile
        float value = tile->getValue();
        float luminance = std::isinf(value) ? 0 : value;

        this->scene()->addPolygon(this->toScreenSpace(this->toCameraSpace(tilerect, camera, cameraFacing), false, camera, cameraFacing)
                                  , Qt::NoPen, QBrush(QColor(luminance*255,luminance*255,luminance*255)));
    }
}


void GameView3d::drawPaths(std::shared_ptr<const LevelObject> levelObject)
{

    // camera info
    std::shared_ptr<PlayerObject> po = levelObject->findChildren<PlayerObject>().at(0);
    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
    auto player = levelObject->findChildren<PlayerObject>().at(0);
    QPointF camera = QPoint(player->getTile().getXPos()*tileSideLen, player->getTile().getYPos()*tileSideLen);
    Direction cameraFacing = player->getFacing();

    std::vector<std::shared_ptr<PathObject>> paths = po->findChildren<PathObject>();
    for(const auto& path : paths) {
        auto tilerect = QRectF(path->getTile().getXPos()*tileSideLen, path->getTile().getYPos()*tileSideLen, tileSideLen, tileSideLen);
        if(this->isCulled(tilerect, camera, cameraFacing)) continue;

        float value = path->getTile().getValue();

        this->scene()->addPolygon(this->toScreenSpace(this->toCameraSpace(tilerect, camera, cameraFacing), false, camera, cameraFacing)
                                  , Qt::NoPen, QBrush(QColor(value*255,value*255,0)));
    }
}

void GameView3d::drawEnemies(std::shared_ptr<const LevelObject> levelObject ) {
    // camera info
    std::shared_ptr<PlayerObject> po = levelObject->findChildren<PlayerObject>().at(0);
    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
    auto player = levelObject->findChildren<PlayerObject>().at(0);
    QPointF camera = QPoint(player->getTile().getXPos()*tileSideLen, player->getTile().getYPos()*tileSideLen);
    Direction cameraFacing = player->getFacing();

    // draw enemies
    std::vector<std::shared_ptr<EnemyObject>> enemies = levelObject->findChildren<EnemyObject>();
    for (const auto &enemy : enemies) {
        auto tilerect = QRectF(enemy->getTile().getXPos()*tileSideLen, enemy->getTile().getYPos()*tileSideLen, tileSideLen, tileSideLen);
        if(this->isCulled(tilerect, camera, cameraFacing)) continue;

        float value = enemy->getTile().getValue();

        this->scene()->addPolygon(this->toScreenSpace(this->toCameraSpace(tilerect, camera, cameraFacing), true, camera, cameraFacing)
                                  , Qt::NoPen, QBrush(Qt::red));
    }

    // draw penemies
    std::vector<std::shared_ptr<PEnemyObject>> penemies = levelObject->findChildren<PEnemyObject>();
    for (const auto &penemy : penemies) {
        auto tilerect = QRectF(penemy->getTile().getXPos()*tileSideLen, penemy->getTile().getYPos()*tileSideLen, tileSideLen, tileSideLen);
        if(this->isCulled(tilerect, camera, cameraFacing)) continue;

        float value = penemy->getTile().getValue();

        this->scene()->addPolygon(this->toScreenSpace(this->toCameraSpace(tilerect, camera, cameraFacing), true, camera, cameraFacing)
                                  , Qt::NoPen, QBrush(QColorConstants::Svg::purple));
    }

    // draw benemies
    std::vector<std::shared_ptr<BEnemyObject>> benemies = levelObject->findChildren<BEnemyObject>();
    for (const auto &benemy : benemies) {
        auto tilerect = QRectF(benemy->getTile().getXPos()*tileSideLen, benemy->getTile().getYPos()*tileSideLen, tileSideLen, tileSideLen);
        if(this->isCulled(tilerect, camera, cameraFacing)) continue;

        float value = benemy->getTile().getValue();

        this->scene()->addPolygon(this->toScreenSpace(this->toCameraSpace(tilerect, camera, cameraFacing), true, camera, cameraFacing)
                                  , Qt::NoPen, QBrush(Qt::blue));

    }
}

void GameView3d::drawItems(std::shared_ptr<const LevelObject> levelObject ) {
    // camera info
    std::shared_ptr<PlayerObject> po = levelObject->findChildren<PlayerObject>().at(0);
    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
    auto player = levelObject->findChildren<PlayerObject>().at(0);
    QPointF camera = QPoint(player->getTile().getXPos()*tileSideLen, player->getTile().getYPos()*tileSideLen);
    Direction cameraFacing = player->getFacing();

    std::vector<std::shared_ptr<HealthPackObject>> healthPacks = levelObject->findChildren<HealthPackObject>();
    for (const auto &hp : healthPacks) {
        auto tilerect = QRectF(hp->getTile().getXPos()*tileSideLen, hp->getTile().getYPos()*tileSideLen, tileSideLen, tileSideLen);
        if(this->isCulled(tilerect, camera, cameraFacing)) continue;

        float value = hp->getTile().getValue();

        this->scene()->addPolygon(this->toScreenSpace(this->toCameraSpace(tilerect, camera, cameraFacing), true, camera, cameraFacing)
                                  , Qt::NoPen, QBrush(Qt::green));
    }

    std::vector<std::shared_ptr<DoorObject>> doors = levelObject->findChildren<DoorObject>();
    for (const auto &d : doors) {
        auto tilerect = QRectF(d->getTile().getXPos()*tileSideLen, d->getTile().getYPos()*tileSideLen, tileSideLen, tileSideLen);
        if(this->isCulled(tilerect, camera, cameraFacing)) continue;
        float value = d->getTile().getValue();

        this->scene()->addPolygon(this->toScreenSpace(this->toCameraSpace(tilerect, camera, cameraFacing), true, camera, cameraFacing)
                                  , Qt::NoPen, QBrush(Qt::cyan));
    }
}

void GameView3d::wheelEvent(QWheelEvent* e) { e->ignore(); }; // ignore wheel event, just to be safe

void GameView3d::draw(std::shared_ptr<const GameObject> state) {

    std::shared_ptr<const GiuGameObject> gState = std::dynamic_pointer_cast<const GiuGameObject>(state);
    std::shared_ptr<LevelObject> levelObject = gState->findChildren<LevelObject>().at(0);
    assert(levelObject); // assert correct type was passed in

    this->rows = levelObject->getRows();
    this->cols = levelObject->getCols();

    this->scene()->clear();

    this->drawTiles(levelObject);
    this->drawPaths(levelObject);
    this->drawEnemies(levelObject);
    this->drawItems(levelObject);
}


QRectF GameView3d::toCameraSpace(QRectF in, QPointF camera, Direction cameraFacing)
{
    auto translated = in.translated(-camera);

    QRectF out;
    switch(cameraFacing) {
    case(Direction::UP):
        out = translated;
        break;
    case(Direction::DOWN):
        out.setLeft(-translated.x());
        out.setTop(-translated.y());
        out.setWidth(-translated.width());
        out.setHeight(-translated.height());
        break;
    case(Direction::LEFT):
        out.setLeft(-translated.y());
        out.setTop(translated.x());
        out.setWidth(-translated.height());
        out.setHeight(translated.width());
        break;
    case(Direction::RIGHT):
        out.setLeft(translated.y());
        out.setTop(-translated.x());
        out.setWidth(translated.height());
        out.setHeight(-translated.width());
        break;

    default: // nothing
        break;
    }

    return out.normalized();
}

QPolygonF GameView3d::toScreenSpace(QRectF in, bool upright, QPointF camera, Direction cameraFacing)
{
    auto& config = GiuGameConfig::getInstance();

    float x1 = in.x(), y1 = in.y(), x2 = x1 + in.width(), y2 = y1 + in.height();
    std::array<float, 1*4> p1, p2, p3, p4; // xyzw

    // transform 2d to: x = x0, z = y0
    //     y-axis
    //     ^
    //     |
    //     |
    //     |
    //     +-----------> x-axis
    //    /
    //   /
    //  v  z-axis

    if(upright) {
        p1 = {x1, 0, y1, 1};
        p2 = {x2, 0, y1, 1};
        p3 = {x1, -config.config3d.cameraZ, y1, 1};
        p4 = {x2, -config.config3d.cameraZ, y1, 1};
    }
    else {
        p1 = {x1, -config.config3d.cameraZ, y1, 1};
        p2 = {x2, -config.config3d.cameraZ, y1, 1};
        p3 = {x1, -config.config3d.cameraZ, y2, 1};
        p4 = {x2, -config.config3d.cameraZ, y2, 1};
    }

    const float pi = std::acos(-1);
    auto n = config.config3d.nearPlane, f = config.config3d.farPlane;
    auto s = 1.f/std::tan(config.config3d.cameraFOV * (pi/360.f));

    std::array<float, 4*4> projectionMatrix = {
        s,  0,  0,              0,
        0,  s,  0,              0,
        0,  0,  -f/(f-n),       -1,
        0,  0,  -(f*n)/(f-n),   0,
    };

    p1 = matmul(p1, projectionMatrix);
    p2 = matmul(p2, projectionMatrix);
    p3 = matmul(p3, projectionMatrix);
    p4 = matmul(p4, projectionMatrix);

    QList<QPointF> points;
    points.emplace_back(((p1[0]/p1[3])+1)*0.5f*config.gameWidth, (1-((p1[1]/p1[3]+1)*0.5f))*config.gameHeight);
    points.emplace_back(((p3[0]/p3[3])+1)*0.5f*config.gameWidth, (1-((p3[1]/p3[3]+1)*0.5f))*config.gameHeight);
    points.emplace_back(((p4[0]/p4[3])+1)*0.5f*config.gameWidth, (1-((p4[1]/p4[3]+1)*0.5f))*config.gameHeight);
    points.emplace_back(((p2[0]/p2[3])+1)*0.5f*config.gameWidth, (1-((p2[1]/p2[3]+1)*0.5f))*config.gameHeight);

    return QPolygonF(points);
}


std::array<float, 1*4> GameView3d::matmul(std::array<float, 1*4> a, std::array<float, 4*4> b) {
    return {
        a[0]*b[0] + a[1]*b[4] + a[2]*b[8] + a[3]*b[12],
        a[0]*b[1] + a[1]*b[5] + a[2]*b[9] + a[3]*b[13],
        a[0]*b[2] + a[1]*b[6] + a[2]*b[10] + a[3]*b[14],
        a[0]*b[3] + a[1]*b[7] + a[2]*b[11] + a[3]*b[15],
    };
}



bool GameView3d::isCulled(QRectF in, QPointF camera, Direction cameraFacing)
{
    auto far = GiuGameConfig::getInstance().config3d.farPlane;
    auto near = GiuGameConfig::getInstance().config3d.nearPlane;
    return !this->toCameraSpace(in, camera, cameraFacing).intersects(QRect(-far, -far, 2*far, far-near));
}

