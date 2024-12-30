#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "GameObject.h"
#include "world.h"
#include <memory>

class EnemyObject;
class PEnemyObject;
class HealthPackObject;

class PlayerObject : public GameObject
{

private:
    PlayerObject(const PlayerObject &) = delete;
    PlayerObject &operator=(const PlayerObject &) = delete;

    void onCollision(std::shared_ptr<GameObject> other);

    void onCollision(std::shared_ptr<EnemyObject> other);
    void onCollision(std::shared_ptr<PEnemyObject> other);
    void onCollision(std::shared_ptr<HealthPackObject> other);

    float poisonAmount;

    qint64 poisonCooldownLeft; // usecs delay
    qint64 moveCooldownLeft; // usecs delay

    void move(qint64 deltaT, int dir);

    std::unique_ptr<Protagonist> playerModel;
    PlayerObject(std::unique_ptr<Protagonist> playerModel);

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    const Protagonist &getProtagonist() const { return *playerModel; }

    float getPoisonAmount() const { return poisonAmount; };
    void stepPoison(qint64 deltaT);

    friend class WorldLoader;


};

#endif // PLAYEROBJECT_H
