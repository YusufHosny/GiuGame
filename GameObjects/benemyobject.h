#ifndef BENEMYOBJECT_H
#define BENEMYOBJECT_H

#include "tileobject.h"

class BEnemyObject : public TileObject
{

private:
    BEnemyObject(const BEnemyObject &) = delete;
    BEnemyObject &operator=(const BEnemyObject &) = delete;

    void onCollision(std::shared_ptr<GameObject> other);

    qint64 blinkTime;
    qint64 blinkTimeLeft;
    bool blinkVisible;

    std::unique_ptr<Enemy> enemyModel;
    BEnemyObject(std::unique_ptr<Enemy> enemyModel);

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    const Enemy &getEnemy() const {return *enemyModel;}

    const Tile& getTile() const override;

    enum AnimationStates {
        IDLE, BLINK
    };

    const unsigned int AnimationFrameCounts[2] = {
        1, 9
    };

    friend class WorldLoader;
};

#endif // BENEMYOBJECT_H
