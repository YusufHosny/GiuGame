#include "autoplaycomponent.h"
#include "playerobject.h"
#include "pathfinder_class.h"
#include "levelobject.h"
#include "enemyobject.h"
#include "healthpackobject.h"
#include "penemyobject.h"



AutoPlayComponent::AutoPlayComponent() {

    this->heurdist = [](const Tile& t1, const Tile& t2) {
        return std::abs(t1.getXPos()-t2.getXPos()) + std::abs(t1.getYPos()-t2.getYPos());
    };
    this->cost = [](const Tile& a, const Tile& b) {
        return b.getValue();
    };

    this->compareNodes = [](const Node& a, const Node& b) {
        return a.f < b.f;
    };
}

void AutoPlayComponent::toggleAutoplay() {
    this->active = !this->active;
}


void AutoPlayComponent::step_component(GameObject& owner) {
    if(!this->active) return;

    PlayerObject& player = dynamic_cast<PlayerObject&>(owner); // throws if non-player owns this component

    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(player.getParent());
    assert(lo);

    // decide what target tile to go to
    const Tile *target = nullptr;

    // check for healthpacks
    if(player.getProtagonist().getHealth() < 30) {
        std::vector<std::shared_ptr<HealthPackObject>> healthpacks = lo->findChildren<HealthPackObject>();
        std::sort(healthpacks.begin(), healthpacks.end(), [this, &player](const std::shared_ptr<HealthPackObject>& a, const std::shared_ptr<HealthPackObject>& b) {
            return this->heurdist(player.getProtagonist(), a->getHP()) < this->heurdist(player.getProtagonist(), b->getHP());
        });
        if(!healthpacks.empty())
            target = &healthpacks.at(0)->getHP();
        else {
            std::cout << "no health packs for autoplay" << std::endl;
            return;
        }
    }
    else {
        // check for enemies
        std::vector<std::shared_ptr<EnemyObject>> enemies = lo->findChildren<EnemyObject>();
        if(!enemies.empty()) {
            std::sort(enemies.begin(), enemies.end(), [this, &player](const std::shared_ptr<EnemyObject>& a, const std::shared_ptr<EnemyObject>& b) {
                return this->heurdist(player.getProtagonist(), a->getEnemy()) < this->heurdist(player.getProtagonist(), b->getEnemy());
            });
            target = &enemies.at(0)->getEnemy();
        }
        else {
            // check for penemies
            std::vector<std::shared_ptr<PEnemyObject>> penemies = lo->findChildren<PEnemyObject>();
            if(!penemies.empty()) {
                std::sort(penemies.begin(), penemies.end(), [this, &player](const std::shared_ptr<PEnemyObject>& a, const std::shared_ptr<PEnemyObject>& b) {
                    return this->heurdist(player.getProtagonist(), a->getPEnemy()) < this->heurdist(player.getProtagonist(), b->getPEnemy());
                });
                target = &penemies.at(0)->getPEnemy();
            }
            else {
                // go to exit
                std::cout << "no exit yet" << std::endl;
                return;
            }
        }
    }


    const std::vector<std::unique_ptr<Tile>> &tiles = lo->getTiles();
    std::vector<Node> nodes;
    for(auto &tile : tiles) {
        nodes.push_back(Node(*tile));
    }

    PathFinder<Node, Tile> pf(nodes, &player.getProtagonist(), target, this->compareNodes, lo->getCols(), this->cost, this->heurdist, 0.4f);

    std::vector<int> path = pf.A_star();
    assert(!path.empty()); // path should never be empty

    switch(path.at(0)) {
    case(0):
        player.move(Direction::UP);
        break;
    case(2):
        player.move(Direction::RIGHT);
        break;
    case(4):
        player.move(Direction::DOWN);
        break;
    case(6):
        player.move(Direction::LEFT);
        break;
    }

}
