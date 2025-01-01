#ifndef BENEMYOBJECT_H
#define BENEMYOBJECT_H

#include "GameObject.h"
#include "world.h"
#include <memory>

class BEnemyObject : public GameObject
{

private:
    BEnemyObject(const BEnemyObject &) = delete;
    BEnemyObject &operator=(const BEnemyObject &) = delete;

    void onCollision(std::shared_ptr<GameObject> other);

    qint64 blinkTime;
    qint64 blinkTimeLeft;
    bool visible;

    std::unique_ptr<Enemy> enemyModel;
    BEnemyObject(std::unique_ptr<Enemy> enemyModel);

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    const Enemy &getEnemy() const {return *enemyModel;}

    friend class WorldLoader;
};

#endif // BENEMYOBJECT_H
