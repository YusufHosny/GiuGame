#include "playerobject.h"
#include "collidercomponent.h"
#include "enemyobject.h"
#include "penemyobject.h"
#include "healthpackobject.h"
#include "levelobject.h"

PlayerObject::PlayerObject(std::unique_ptr<Protagonist> playerModel): playerModel(std::move(playerModel)), GameObject("Player") {}

void PlayerObject::init()
{
    this->components.emplace_back(new ColliderComponent(
        [this](std::shared_ptr<GameObject> other) {
            this->onCollision(other);
        },
        [this]() {
            // getPosition
            std::array<int, 2> out {this->playerModel->getXPos(), this->playerModel->getYPos()};
            return out;
        }
    ));

}

void PlayerObject::step(qint64 deltaT, std::set<GameInput> inputs)
{
    for(auto &input: inputs) {
        if(input.type == GameInputType::PLAYERMOVE) { // TODO CHECK MOVE VALID
            this->move(input.parameter);
        }
    }
}

void PlayerObject::move(int dir) {
    int x = this->playerModel->getXPos(), y = this->playerModel->getYPos();

    switch(dir) {
        case(Direction::UP):
            y -= 1;
            break;

        case(Direction::DOWN):
            y += 1;
            break;

        case(Direction::LEFT):
            x -= 1;
            break;

        case(Direction::RIGHT):
            x += 1;
            break;
    }

    this->playerModel->setPos(x, y);

    float energy = this->playerModel->getEnergy();
    std::shared_ptr<LevelObject> lo = std::dynamic_pointer_cast<LevelObject>(this->parent);
    float targetValue = lo->getTile(x, y)->getValue();
    this->playerModel->setEnergy(energy - targetValue);
}


void PlayerObject::onCollision(std::shared_ptr<GameObject> other)
{
    if(auto e = std::dynamic_pointer_cast<EnemyObject>(other)) {
        std::cout << "collided with enemy" << std::endl;
    }
    else if(auto pe = std::dynamic_pointer_cast<PEnemyObject>(other)) {
        std::cout << "collided with penemy" << std::endl;
    }
    else if(auto hp = std::dynamic_pointer_cast<HealthPackObject>(other)) {
        std::cout << "collided with healthpack" << std::endl;
    }
}


std::string PlayerObject::dumpData() const
{
    return ""; // TODO
}
