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

GameView2d::GameView2d(QWidget *parent, std::shared_ptr<const GameObject> state): QGraphicsScene(parent) {

    this->clear();

    // cast input to a level object
    std::shared_ptr<const LevelObject> levelObject = std::dynamic_pointer_cast<const LevelObject>(state);
    assert(levelObject); // assert correct type was passed in

    this->rows = levelObject->getRows();
    this->cols = levelObject->getCols();

    int tileWidth = 50;

    // draw tiles
    for (const auto &tile : levelObject->getTiles()) {
        float value = tile->getValue();
        if (std::isinf(value)) value = 0;

        int grayScale = static_cast<int>(value * 255);
        QBrush brush(QColor(grayScale, grayScale, grayScale));

        auto rectItem = this->addRect(tile->getXPos() * tileWidth, tile->getYPos() * tileWidth, tileWidth, tileWidth, QPen(Qt::NoPen), brush);
        tileViews.push_back(rectItem);
    }

    // draw player
    std::shared_ptr<PlayerObject> po = levelObject->findChildren<PlayerObject>().at(0);
    playerView = new PlayerView2D();
    this->addItem(playerView);
    playerView->draw(po);

    // draw gui
    int barWidth = tileWidth;
    int maxBarHeight = 200;
    int leftMargin = (this->rows + 2) * tileWidth;
    int topOffset = 2 * tileWidth;

    healthBar = this->addRect(leftMargin, topOffset, barWidth, maxBarHeight, QPen(Qt::NoPen), QBrush(Qt::green));
    energyBar = this->addRect(leftMargin + 2*tileWidth, topOffset, barWidth, maxBarHeight, QPen(Qt::NoPen), QBrush(Qt::green));

    QGraphicsTextItem *hpLabel = this->addText("Health");
    hpLabel->setDefaultTextColor(Qt::white);
    hpLabel->setFont(QFont("Arial", 12));
    hpLabel->setPos(leftMargin + (tileWidth/5), topOffset + maxBarHeight + (tileWidth/5));

    QGraphicsTextItem *energyLabel = this->addText("Energy");
    energyLabel->setDefaultTextColor(Qt::white);
    energyLabel->setFont(QFont("Arial", 12));
    energyLabel->setPos(leftMargin + 2*tileWidth - tileWidth/5, topOffset + maxBarHeight + (tileWidth/5));

    // draw enemies
    std::vector<std::shared_ptr<EnemyObject>> enemies = levelObject->findChildren<EnemyObject>();
    for (const auto &enemy : enemies) {
        EnemyView2D *ev = new EnemyView2D();
        this->addItem(ev);
        ev->draw(enemy);
        enemyViews.push_back(ev);
    }

    // draw penemies
    std::vector<std::shared_ptr<PEnemyObject>> penemies = levelObject->findChildren<PEnemyObject>();
    for (const auto &penemy : penemies) {
        PEnemyView2D *pev = new PEnemyView2D();
        this->addItem(pev);
        pev->draw(penemy);
        penemyViews.push_back(pev);
    }

    // TODO draw xenemies

    // draw health packs
    std::vector<std::shared_ptr<HealthPackObject>> healthPacks = levelObject->findChildren<HealthPackObject>();
    for (const auto &hp : healthPacks) {
        HealthPackView2D *hpv = new HealthPackView2D();
        this->addItem(hpv);
        hpv->draw(hp);
        healthPackViews.push_back(hpv);
    }


}


void GameView2d::draw(std::shared_ptr<const GameObject> state) {
    this->clear();

    // redraw player
    std::shared_ptr<const LevelObject> lo = std::dynamic_pointer_cast<const LevelObject>(state);

    std::shared_ptr<PlayerObject> po = lo->findChildren<PlayerObject>().at(0);
    playerView->draw(po);

    // redraw enemies
    std::vector<std::shared_ptr<EnemyObject>> enemies = lo->findChildren<EnemyObject>();
    for (int i = 0; i < enemyViews.size(); i++) {
        enemyViews[i]->draw(enemies[i]);
    }

    // redraw penemies
    std::vector<std::shared_ptr<PEnemyObject>> penemies = lo->findChildren<PEnemyObject>();
    for (int i = 0; i < penemyViews.size(); i++) {
        penemyViews[i]->draw(penemies[i]);
    }

    // redraw health and energy
    int maxBarHeight = 200;
    int health = po->getProtagonist().getHealth();
    int energy = po->getProtagonist().getEnergy();

    int healthHeight = static_cast<int>((health / 100.0) * maxBarHeight);
    healthBar->setRect(10, 10 + (maxBarHeight - healthHeight), 20, healthHeight);

    int energyHeight = static_cast<int>((energy / 100.0) * maxBarHeight);
    energyBar->setRect(40, 10 + (maxBarHeight - energyHeight), 20, energyHeight);

}

