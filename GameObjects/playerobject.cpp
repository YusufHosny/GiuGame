#include "playerobject.h"

PlayerObject::PlayerObject(std::unique_ptr<Protagonist> playerModel): playerModel(std::move(playerModel)) {}

void PlayerObject::init_impl()
{

}

void PlayerObject::step_impl(qint64 deltaT, std::set<GameInput> inputs)
{

}

std::string PlayerObject::dumpData() const
{
    return ""; // TODO
}
