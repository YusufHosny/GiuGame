#include "autoplaycomponent.h"

#include "levelobject.h"
#include "playerobject.h"
#include "healthpackobject.h"
#include "enemyobject.h"
#include "penemyobject.h"
#include "benemyobject.h"
#include "tileobject.h"

std::function<float(const Tile& t1, const Tile& t2)> manhattandist = [](const Tile& a, const Tile& b) {
          return std::abs(a.getXPos()-b.getXPos()) + std::abs(a.getYPos()-b.getYPos());
      };
std::function<float(const Tile& t1, const Tile& t2)> cost = [](const Tile& a, const Tile& b) {
    return b.getValue();
};
std::function<bool(const Node& t1, const Node& t2)> compareNodes = [](const Node& a, const Node& b) {
    return std::less<float>()(b.f, a.f);
};

AutoPlayComponent::AutoPlayComponent() {
    this->pf = new PathFinder<Node, Tile>(this->nodes, nullptr, nullptr, compareNodes, 1, cost, manhattandist, 0.9f);
    this->target = nullptr;
}

AutoPlayComponent::~AutoPlayComponent() {
    delete this->pf;
}


const Tile* AutoPlayComponent::getTarget() const
{
    return this->target;
}

void AutoPlayComponent::setTarget(const Tile* t)
{
    this->target = t;
}


void AutoPlayComponent::step_component(GameObject& owner, qint64 deltaT) {

    PlayerObject& player = dynamic_cast<PlayerObject&>(owner); // throws if non-player owns this component
    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(player.getParent());

    // decide what target tile to go to
    if(this->target) {
        if(this->target->getXPos() == player.getTile().getXPos() && this->target->getYPos() == player.getTile().getYPos()) this->target = nullptr;
    }
    if(!this->target || this->path.empty()) this->updatePath(player, lo);

    switch(this->path.at(0)) {
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

    this->path.erase(this->path.begin());

}

void AutoPlayComponent::updatePath(PlayerObject& player, std::shared_ptr<LevelObject> lo)
{
    this->target = this->chooseTarget(player, lo);

    const std::vector<std::unique_ptr<Tile>> &tiles = lo->getTiles();
    nodes.clear();
    for(auto& tile : tiles) {
        nodes.push_back(Node(*tile));
    }
    this->pf->updateNodesWidth(this->nodes, lo->getCols());
    this->pf->setStart(&player.getProtagonist());
    this->pf->setDestination(this->target);

    this->path = pf->A_star();
    assert(!path.empty()); // path should never be empty
}

const Tile* AutoPlayComponent::chooseTarget(PlayerObject& player, std::shared_ptr<LevelObject> lo)
{
    if(player.getProtagonist().getHealth() < 30) {
        if(auto out = this->nearestHealth(player, lo)) return out;
        else if(auto out = this->nearestEnemy(player, lo)) return out;
        else return this->nearestExit(player, lo);
    }
    else {
        if(auto out = this->nearestEnemy(player, lo)) return out;
        else return this->nearestExit(player, lo);
    }
}

const Tile *AutoPlayComponent::nearestEnemy(PlayerObject& player, std::shared_ptr<LevelObject> lo)
{
    std::vector<std::shared_ptr<EnemyObject>> enemies = lo->findChildren<EnemyObject>();
    std::vector<std::shared_ptr<PEnemyObject>> penemies = lo->findChildren<PEnemyObject>();
    std::vector<std::shared_ptr<BEnemyObject>> benemies = lo->findChildren<BEnemyObject>();

    // concat all enemies into 1 big vector of tileobjects
    std::vector<std::shared_ptr<TileObject>> allEnemies;
    for(auto &e : enemies) {
        allEnemies.emplace_back(std::dynamic_pointer_cast<TileObject>(e));
    }
    for(auto &e : penemies) {
        allEnemies.emplace_back(std::dynamic_pointer_cast<TileObject>(e));
    }
    for(auto &e : benemies) {
        allEnemies.emplace_back(std::dynamic_pointer_cast<TileObject>(e));
    }

    // sort all enemies by heuristic
    std::sort(penemies.begin(), penemies.end(), [this, &player](const std::shared_ptr<TileObject>& a, const std::shared_ptr<TileObject>& b) {
        return manhattandist(player.getProtagonist(), a->getTile()) < manhattandist(player.getProtagonist(), b->getTile());
    });

    return allEnemies.empty() ? nullptr : &allEnemies.at(0)->getTile();
}

const Tile *AutoPlayComponent::nearestHealth(PlayerObject& player, std::shared_ptr<LevelObject> lo)
{
    std::vector<std::shared_ptr<HealthPackObject>> healths = lo->findChildren<HealthPackObject>();

    // sort all health by heuristic
    std::sort(healths.begin(), healths.end(), [this, &player](const std::shared_ptr<TileObject>& a, const std::shared_ptr<TileObject>& b) {
        return manhattandist(player.getProtagonist(), a->getTile()) < manhattandist(player.getProtagonist(), b->getTile());
    });

    return healths.empty() ? nullptr : &healths.at(0)->getTile();
}

const Tile *AutoPlayComponent::nearestExit(PlayerObject& player, std::shared_ptr<LevelObject> lo)
{
    return nullptr; // TODO
}
