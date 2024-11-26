#include "enemyobject.h"

EnemyObject::EnemyObject(std::unique_ptr<Enemy> enemyModel): enemyModel(std::move(enemyModel)) {}

void EnemyObject::init()
{

}

void EnemyObject::step(qint64 deltaT, std::set<GameInput> inputs)
{

}

std::string EnemyObject::dumpData() const
{
    return ""; // TODO
}
