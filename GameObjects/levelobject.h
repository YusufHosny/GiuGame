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
    std::vector<std::unique_ptr<Tile>> healthPacks;

    LevelObject(std::vector<std::unique_ptr<Tile>> tiles, std::vector<std::unique_ptr<Tile>> healthPacks, int rows, int cols);
    int cols, rows;

public:
    void init_impl() override;
    void step_impl(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    friend class WorldLoader;
};

#endif // LEVELOBJECT_H
