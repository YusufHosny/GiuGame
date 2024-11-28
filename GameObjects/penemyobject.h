#ifndef PENEMYOBJECT_H
#define PENEMYOBJECT_H

#include "GameObject.h"
#include "world.h"
#include <memory>

class PEnemyObject : public GameObject
{

private:
    PEnemyObject(const PEnemyObject &) = delete;
    PEnemyObject &operator=(const PEnemyObject &) = delete;

    std::unique_ptr<PEnemy> pEnemyModel;
    PEnemyObject(std::unique_ptr<PEnemy> pEnemyModel);

public:
    void init_impl() override;
    void step_impl(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    friend class WorldLoader;
};

#endif // PENEMYOBJECT_H
