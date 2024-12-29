#include "playerobject.h"
#include "collidercomponent.h"
#include "enemyobject.h"
#include "penemyobject.h"
#include "healthpackobject.h"

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
            switch(input.parameter) {
            case(0): { // up
                int x = this->playerModel->getXPos();
                int y = this->playerModel->getYPos();
                this->playerModel->setPos(x, y-1);
                break;
            }
            case(1): { // down
                int x = this->playerModel->getXPos();
                int y = this->playerModel->getYPos();
                this->playerModel->setPos(x, y+1);
                break;
            }
            case(2): { // left
                int x = this->playerModel->getXPos();
                int y = this->playerModel->getYPos();
                this->playerModel->setPos(x-1, y);
                break;
            }
            case(3): { // right
                int x = this->playerModel->getXPos();
                int y = this->playerModel->getYPos();
                this->playerModel->setPos(x+1, y);
                break;
            }


            }
        }
    }
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
