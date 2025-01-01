#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "tileobject.h"

class EnemyObject;
class BEnemyObject;
class PEnemyObject;
class HealthPackObject;

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

    float poisonAmount;

    qint64 poisonCooldownLeft; // usecs delay
    qint64 moveCooldownLeft; // usecs delay

    bool showPath;

    std::unique_ptr<Protagonist> playerModel;
    PlayerObject(std::unique_ptr<Protagonist> playerModel);

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    const Protagonist& getProtagonist() const { return *playerModel; }

    void move(int dir);

    void setShowPath(bool showPath);
    bool isShowPath() const;

    float getPoisonAmount() const { return poisonAmount; };
    void stepPoison(qint64 deltaT);

    const Tile& getTile() const override;

    friend class WorldLoader;


};

#endif // PLAYEROBJECT_H
