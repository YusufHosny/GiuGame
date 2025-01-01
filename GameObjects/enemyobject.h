#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "tileobject.h"

class EnemyObject : public TileObject
{

private:
    EnemyObject(const EnemyObject &) = delete;
    EnemyObject &operator=(const EnemyObject &) = delete;

    void onCollision(std::shared_ptr<GameObject> other);

    std::unique_ptr<Enemy> enemyModel;
    EnemyObject(std::unique_ptr<Enemy> enemyModel);

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    const Enemy& getEnemy() const {return *enemyModel;}

    const Tile& getTile() const override;

    friend class WorldLoader;
};

#endif // ENEMYOBJECT_H
