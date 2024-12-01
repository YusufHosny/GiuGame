#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include "GameObject.h"
#include "world.h"
#include <memory>
#include <vector>

class LevelObject : public GameObject
{

private:
    LevelObject(const LevelObject &) = delete;
    LevelObject &operator=(const LevelObject &) = delete;

    std::vector<std::unique_ptr<Tile>> tiles;

    LevelObject(std::vector<std::unique_ptr<Tile>> tiles, int rows, int cols);
    int cols, rows;

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    friend class WorldLoader;

    const std::vector<std::unique_ptr<Tile>> &getTiles() const { return tiles;}
};

#endif // LEVELOBJECT_H
