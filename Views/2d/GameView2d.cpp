#include "GameView2d.h"
#include "levelobject.h"
#include "playerview2d.h"
#include "playerobject.h"
#include "enemyview2d.h"
#include "enemyobject.h"
#include "penemyobject.h"
#include "penemyview2d.h"

GameView2d::GameView2d(QWidget *parent): QGraphicsScene(parent) {

}

void GameView2d::draw(std::shared_ptr<const GameObject> state) {
    this->clear();

    std::shared_ptr<const LevelObject> lo = std::dynamic_pointer_cast<const LevelObject>(state);

    // DRAWING TILES
    for (const auto &tile : lo->getTiles()) {
        float value = tile->getValue();

        if (std::isinf(value)) {
            value = 0;
        }

        int grayScale = static_cast<int>(value * 255);

        QBrush brush(QColor(grayScale, grayScale, grayScale));
        this->addRect(tile->getXPos()*50, tile->getYPos()*50, 50, 50, QPen(Qt::NoPen), brush);
    }


    // DRAWING PLAYER
    std::shared_ptr<PlayerObject> po = lo->findChildrenByLabel<PlayerObject>("Player").at(0);
    PlayerView2D *pv = new PlayerView2D();
    this->addItem(pv);
    pv->draw(po);


    // DRAWING ENEMIES
    std::vector<std::shared_ptr<EnemyObject>> enemies = lo->findChildrenByLabel<EnemyObject>("Enemy");

    for (const auto& enemy : enemies) {
        if (enemy) {
            EnemyView2D *ev = new EnemyView2D();
            this->addItem(ev);
            ev->draw(enemy);
        }
    }


    // DRAWING PENEMIES
     std::vector<std::shared_ptr<PEnemyObject>> penemies = lo->findChildrenByLabel<PEnemyObject>("PEnemy");

    for (const auto& penemy : penemies) {
        if (penemy) {
            PEnemyView2D *pev = new PEnemyView2D();
            this->addItem(pev);
            pev->draw(penemy);
        }
    }

}

