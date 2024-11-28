#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "GameObject.h"
#include "world.h"
#include <memory>

class EnemyObject : public GameObject
{

private:
    EnemyObject(const EnemyObject &) = delete;
    EnemyObject &operator=(const EnemyObject &) = delete;

    std::unique_ptr<Enemy> enemyModel;
    EnemyObject(std::unique_ptr<Enemy> enemyModel);

public:
    void init_impl() override;
    void step_impl(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    friend class WorldLoader;
};

#endif // ENEMYOBJECT_H
