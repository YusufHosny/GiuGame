#include "GameView2d.h"
#include "levelobject.h"
#include "playerview2d.h"
#include "playerobject.h"
#include "enemyview2d.h"
#include "enemyobject.h"
#include "penemyobject.h"
#include "penemyview2d.h"

GameView2d::GameView2d(QWidget *parent, std::shared_ptr<const GameObject> state): QGraphicsScene(parent) {

    this->clear();

    std::shared_ptr<const LevelObject> levelObject = std::dynamic_pointer_cast<const LevelObject>(state);

    // ADDING TILES
    for (const auto &tile : levelObject->getTiles()) {
        float value = tile->getValue();
        if (std::isinf(value)) value = 0;

        int grayScale = static_cast<int>(value * 255);
        QBrush brush(QColor(grayScale, grayScale, grayScale));

        auto rectItem = this->addRect(tile->getXPos() * 50, tile->getYPos() * 50, 50, 50, QPen(Qt::NoPen), brush);
        tileViews.push_back(rectItem);
    }

    // ADDING PLAYER
    std::shared_ptr<PlayerObject> po = levelObject->findChildrenByLabel<PlayerObject>("Player").at(0);
    playerView = new PlayerView2D();
    this->addItem(playerView);
    playerView->draw(po);

    // ADDING ENEMIES
    std::vector<std::shared_ptr<EnemyObject>> enemies = levelObject->findChildrenByLabel<EnemyObject>("Enemy");
    for (const auto &enemy : enemies) {
        if (enemy) {
            EnemyView2D *ev = new EnemyView2D();
            this->addItem(ev);
            ev->draw(enemy);
            enemyViews.push_back(ev);
        }
    }

    // ADDING PENEMIES
    std::vector<std::shared_ptr<PEnemyObject>> penemies = levelObject->findChildrenByLabel<PEnemyObject>("PEnemy");
    for (const auto &penemy : penemies) {
        if (penemy) {
            PEnemyView2D *pev = new PEnemyView2D();
            this->addItem(pev);
            pev->draw(penemy);
            penemyViews.push_back(pev);
        }
    }
}


void GameView2d::draw(std::shared_ptr<const GameObject> state) {
    this->clear();

    // REDRAW PLAYER
    std::shared_ptr<const LevelObject> lo = std::dynamic_pointer_cast<const LevelObject>(state);
    if (playerView) {
        std::shared_ptr<PlayerObject> po = lo->findChildrenByLabel<PlayerObject>("Player").at(0);
        playerView->draw(po);
    }

    // REDRAW ENEMIES
    std::vector<std::shared_ptr<EnemyObject>> enemies = lo->findChildrenByLabel<EnemyObject>("Enemy");
    for (size_t i = 0; i < enemyViews.size(); ++i) {
        if (i < enemies.size() && enemies[i]) {
            enemyViews[i]->draw(enemies[i]);
        }
    }

    // REDRAW PENEMIES
    std::vector<std::shared_ptr<PEnemyObject>> penemies = lo->findChildrenByLabel<PEnemyObject>("PEnemy");
    for (size_t i = 0; i < penemyViews.size(); ++i) {
        if (i < penemies.size() && penemies[i]) {
            penemyViews[i]->draw(penemies[i]);
        }
    }

}

