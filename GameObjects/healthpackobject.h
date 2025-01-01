#ifndef HEALTHPACKOBJECT_H
#define HEALTHPACKOBJECT_H

#include "tileobject.h"

class HealthPackObject: public TileObject
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

    const Tile& getHP() const {return *tile;};

    const Tile& getTile() const override;

    friend class WorldLoader;
};

#endif // HEALTHPACKOBJECT_H
