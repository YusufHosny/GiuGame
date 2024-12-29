#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "GameObject.h"
#include "world.h"
#include <memory>

class PlayerObject : public GameObject
{

private:
    PlayerObject(const PlayerObject &) = delete;
    PlayerObject &operator=(const PlayerObject &) = delete;

    void onCollision(std::shared_ptr<GameObject> other);

    void move(int dir);

    std::unique_ptr<Protagonist> playerModel;
    PlayerObject(std::unique_ptr<Protagonist> playerModel);

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    const Protagonist &getProtagonist() const {return *playerModel;}

    friend class WorldLoader;


};

#endif // PLAYEROBJECT_H
