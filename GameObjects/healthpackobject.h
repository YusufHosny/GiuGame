#ifndef HEALTHPACKOBJECT_H
#define HEALTHPACKOBJECT_H

#include "tileobject.h"

class HealthPackObject: public TileObject
{
private:
    HealthPackObject(const HealthPackObject &) = delete;
    HealthPackObject &operator=(const HealthPackObject &) = delete;

    std::unique_ptr<Tile> tile;
    HealthPackObject(std::unique_ptr<Tile> tile);

public:
    void init() override;

    std::string dumpData() const override;

    const Tile& getHP() const {return *tile;};

    const Tile& getTile() const override;

    enum AnimationStates {
        IDLE
    };

    const unsigned int AnimationFrameCounts[1] = {
        9
    };

    friend class WorldLoader;
};

#endif // HEALTHPACKOBJECT_H
