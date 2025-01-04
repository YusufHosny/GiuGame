#ifndef DOOROBJECT_H
#define DOOROBJECT_H

#include "tileobject.h"
#include "world.h"

class DoorObject : public TileObject
{
private:
    DoorObject(const DoorObject &) = delete;
    DoorObject &operator=(const DoorObject &) = delete;

    DoorObject(QString targetLevel, int x, int y);
    const QString target;
    int x, y;

    Tile t;

    bool loaded;

public:
    void init() override;

    std::string dumpData() const override;

    QString getTarget() const;

    const Tile& getTile() const override;

    enum AnimationStates {
        IDLE
    };

    const unsigned int AnimationFrameCounts[1] = {
        10
    };

    friend class WorldLoader;

};

#endif // DOOROBJECT_H
