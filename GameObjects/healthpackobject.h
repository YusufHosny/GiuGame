#ifndef HEALTHPACKOBJECT_H
#define HEALTHPACKOBJECT_H

#include "GameObject.h"
#include "world.h"
#include <memory>

class HealthPackObject: public GameObject
{
private:
    HealthPackObject(const HealthPackObject &) = delete;
    HealthPackObject &operator=(const HealthPackObject &) = delete;

    void onCollision(std::shared_ptr<GameObject> other);

    std::unique_ptr<Tile> tile;
    HealthPackObject(std::unique_ptr<Tile> tile);

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    const Tile &getHP() const {return *tile;};

    friend class WorldLoader;
};

#endif // HEALTHPACKOBJECT_H
