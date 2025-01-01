#ifndef PENEMYOBJECT_H
#define PENEMYOBJECT_H

#include "tileobject.h"

class PEnemyObject : public TileObject
{

private:
    PEnemyObject(const PEnemyObject &) = delete;
    PEnemyObject &operator=(const PEnemyObject &) = delete;

    void onCollision(std::shared_ptr<GameObject> other);

    std::unique_ptr<PEnemy> pEnemyModel;
    PEnemyObject(std::unique_ptr<PEnemy> pEnemyModel);

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    const PEnemy &getPEnemy() const {return *pEnemyModel;}

    const Tile& getTile() const override;

    friend class WorldLoader;
};

#endif // PENEMYOBJECT_H
