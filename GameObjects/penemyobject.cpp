#include "penemyobject.h"

PEnemyObject::PEnemyObject(std::unique_ptr<PEnemy> pEnemyModel): pEnemyModel(std::move(pEnemyModel)), GameObject("PEnemy") {}

void PEnemyObject::init()
{

}

void PEnemyObject::step(qint64 deltaT, std::set<GameInput> inputs)
{

}

std::string PEnemyObject::dumpData() const
{
    return ""; // TODO
}
