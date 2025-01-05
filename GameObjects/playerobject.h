#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "tileobject.h"

class EnemyObject;
class BEnemyObject;
class PEnemyObject;
class HealthPackObject;
class DoorObject;

class PlayerObject : public TileObject
{

private:
    PlayerObject(const PlayerObject &) = delete;
    PlayerObject &operator=(const PlayerObject &) = delete;

    void onCollision(std::shared_ptr<GameObject> other);

    void onCollision(std::shared_ptr<EnemyObject> other);
    void onCollision(std::shared_ptr<BEnemyObject> other);
    void onCollision(std::shared_ptr<PEnemyObject> other);
    void onCollision(std::shared_ptr<HealthPackObject> other);
    void onCollision(std::shared_ptr<DoorObject> other);

    float poisonAmount;

    qint64 poisonCooldownLeft; // usecs delay
    qint64 moveCooldownLeft; // usecs delay

    bool showPath;

    std::unique_ptr<Protagonist> playerModel;
    PlayerObject(std::unique_ptr<Protagonist> playerModel);

    void stepPoison(qint64 deltaT);
    void updateAnimation();
    void setState(unsigned int state);

    Direction facing;
    unsigned int state;

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    const Protagonist& getProtagonist() const;

    bool isDead() const;

    bool move(int dir);

    void setShowPath(bool showPath);
    bool isShowPath() const;

    float getPoisonAmount() const;

    const Tile& getTile() const override;

    enum AnimationStates {
        IDLEUP, IDLEDOWN, IDLELEFT, IDLERIGHT,
        WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT,
        FIGHTING,
        DYING,
    };

    const unsigned int AnimationFrameCounts[10] = {
        1, 1, 1, 1,
        10, 10, 10, 10,
        4,
        5
    };

    friend class WorldLoader;

};

#endif // PLAYEROBJECT_H
