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
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    const PEnemy &getPEnemy() const {return *pEnemyModel;}


    friend class WorldLoader;
};

#endif // PENEMYOBJECT_H
