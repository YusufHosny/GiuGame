#include "enemyobject.h"

EnemyObject::EnemyObject(std::unique_ptr<Enemy> enemyModel): enemyModel(std::move(enemyModel)) {}

void EnemyObject::init_impl()
{

}

void EnemyObject::step_impl(qint64 deltaT, std::set<GameInput> inputs)
{

}

std::string EnemyObject::dumpData() const
{
    return ""; // TODO
}
