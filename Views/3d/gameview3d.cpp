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

}

int GameView3d::getCols() const {
    return this->cols;
}

void GameView3d::drawTiles(std::shared_ptr<const LevelObject> levelObject) {
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



void GameView3d::drawPaths(std::shared_ptr<const LevelObject> levelObject)
{
    std::shared_ptr<PlayerObject> po = levelObject->findChildren<PlayerObject>().at(0);
    std::vector<std::shared_ptr<PathObject>> paths = po->findChildren<PathObject>();
    for(const auto& path : paths) {
        ItemView* pathView = factory.makePath();
        this->scene()->addItem(pathView);
        pathView->draw(path);
    }
}

void GameView3d::drawEnemies(std::shared_ptr<const LevelObject> levelObject ) {
    // draw enemies
    std::vector<std::shared_ptr<EnemyObject>> enemies = levelObject->findChildren<EnemyObject>();
    for (const auto &enemy : enemies) {
        ItemView* ev = factory.makeEnemy();
        this->scene()->addItem(ev);
        ev->draw(enemy);

        // draw enemy gui
        int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
        QGraphicsTextItem* enemyDmgLabel = this->scene()->addText(QString::number(enemy->getEnemy().getValue(), 'g', 3));
        enemyDmgLabel->setDefaultTextColor(Qt::red);
        enemyDmgLabel->setFont(QFont("Arial", 8));
        enemyDmgLabel->setPos((enemy->getEnemy().getXPos()+.1)*tileSideLen, (enemy->getEnemy().getYPos()-.5)*tileSideLen);
    }

    // draw penemies
    std::vector<std::shared_ptr<PEnemyObject>> penemies = levelObject->findChildren<PEnemyObject>();
    for (const auto &penemy : penemies) {
        ItemView* pev = factory.makePEnemy();
        this->scene()->addItem(pev);
        pev->draw(penemy);

        // draw enemy gui
        int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
        QGraphicsTextItem* enemyDmgLabel = this->scene()->addText(QString::number(penemy->getPEnemy().getValue(), 'g', 3));
        enemyDmgLabel->setDefaultTextColor(QColorConstants::Svg::purple);
        enemyDmgLabel->setFont(QFont("Arial", 8));
        enemyDmgLabel->setPos((penemy->getPEnemy().getXPos()+.1)*tileSideLen, (penemy->getPEnemy().getYPos()-.5)*tileSideLen);
    }

    // draw benemies
    std::vector<std::shared_ptr<BEnemyObject>> benemies = levelObject->findChildren<BEnemyObject>();
    for (const auto &benemy : benemies) {
        ItemView* bev = factory.makeBEnemy();
        this->scene()->addItem(bev);
        bev->draw(benemy);

        // draw enemy gui
        int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
        QGraphicsTextItem* enemyDmgLabel = this->scene()->addText(QString::number(benemy->getEnemy().getValue(), 'g', 3));
        enemyDmgLabel->setDefaultTextColor(Qt::red);
        enemyDmgLabel->setFont(QFont("Arial", 8));
        enemyDmgLabel->setPos((benemy->getEnemy().getXPos()+.1)*tileSideLen, (benemy->getEnemy().getYPos()-.5)*tileSideLen);

    }
}

void GameView3d::drawItems(std::shared_ptr<const LevelObject> levelObject ) {
    std::vector<std::shared_ptr<HealthPackObject>> healthPacks = levelObject->findChildren<HealthPackObject>();
    for (const auto &hp : healthPacks) {
        ItemView* hpv = factory.makeHealthPack();
        this->scene()->addItem(hpv);
        hpv->draw(hp);

        // draw hp gui
        int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
        QGraphicsTextItem* healthLabel = this->scene()->addText(QString::number(hp->getHP().getValue(), 'g', 3));
        healthLabel->setDefaultTextColor(Qt::green);
        healthLabel->setFont(QFont("Arial", 8));
        healthLabel->setPos((hp->getHP().getXPos()+.1)*tileSideLen, (hp->getHP().getYPos()-.5)*tileSideLen);
    }

    std::vector<std::shared_ptr<DoorObject>> doors = levelObject->findChildren<DoorObject>();
    for (const auto &d : doors) {
        ItemView* dv = factory.makeDoor();
        this->scene()->addItem(dv);
        dv->draw(d);
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

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
    auto xstart = 3, ystart = 3;
    auto r11 = QRect(xstart*tileSideLen, ystart*tileSideLen, tileSideLen, tileSideLen);
    auto r12 = QRect((xstart+1)*tileSideLen, ystart*tileSideLen, tileSideLen, tileSideLen);
    auto r21 = QRect(xstart*tileSideLen, (ystart+1)*tileSideLen, tileSideLen, tileSideLen);
    auto r22 = QRect((xstart+1)*tileSideLen, (ystart+1)*tileSideLen, tileSideLen, tileSideLen);

    auto camera = QPointF(4*tileSideLen, 8*tileSideLen);
    auto cameraFacing = Direction::UP;

    this->scene()->addPolygon(this->toScreenSpace(this->toCameraSpace(r11, camera, cameraFacing), false, camera, cameraFacing)
                              , Qt::NoPen, QBrush(Qt::black));
    this->scene()->addPolygon(this->toScreenSpace(this->toCameraSpace(r12, camera, cameraFacing), false, camera, cameraFacing)
                              , Qt::NoPen, QBrush(Qt::white));
    this->scene()->addPolygon(this->toScreenSpace(this->toCameraSpace(r21, camera, cameraFacing), false, camera, cameraFacing)
                              , Qt::NoPen, QBrush(Qt::white));
    this->scene()->addPolygon(this->toScreenSpace(this->toCameraSpace(r22, camera, cameraFacing), false, camera, cameraFacing)
                              , Qt::NoPen, QBrush(Qt::black));

    // this->drawTiles(levelObject);
    // this->drawPaths(levelObject);
    // this->drawEnemies(levelObject);
    // this->drawItems(levelObject);
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

    // transform 2d to: x = x0, z = -y0
    //     y-axis
    //     ^
    //     |  7 z-axis
    //     | /
    //     |/
    //     +-----------> x-axis

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



bool GameView3d::isRendered(QRectF in, QPointF camera, Direction cameraFacing)
{
    return true; // for now
}

