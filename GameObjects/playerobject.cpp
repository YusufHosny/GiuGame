#include "playerobject.h"

PlayerObject::PlayerObject(std::unique_ptr<Protagonist> playerModel): playerModel(std::move(playerModel)) {}

void PlayerObject::init()
{

}

void PlayerObject::step(qint64 deltaT, std::set<GameInput> inputs)
{

}

std::string PlayerObject::dumpData() const
{
    return ""; // TODO
}
