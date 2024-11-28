#include "penemyobject.h"

PEnemyObject::PEnemyObject(std::unique_ptr<PEnemy> pEnemyModel): pEnemyModel(std::move(pEnemyModel)) {}

void PEnemyObject::init_impl()
{

}

void PEnemyObject::step_impl(qint64 deltaT, std::set<GameInput> inputs)
{

}

std::string PEnemyObject::dumpData() const
{
    return ""; // TODO
}
