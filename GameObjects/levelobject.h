#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include "gameobject.h"
#include "world.h"
#include <memory>
#include <vector>

class LevelObject : public GameObject
{

private:
    LevelObject(const LevelObject &) = delete;
    LevelObject &operator=(const LevelObject &) = delete;

    std::vector<std::unique_ptr<Tile>> tiles;

    int zoomStatus; // -1: zoom in, 0: no change, 1: zoom out
    bool cameraReset;
    Direction cameraMovement;

    LevelObject(std::vector<std::unique_ptr<Tile>> tiles, int rows, int cols);
    int cols, rows;

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    friend class WorldLoader;

    const std::vector<std::unique_ptr<Tile>> &getTiles() const;
    const std::unique_ptr<Tile> &getTile(int x, int y);

    const int getRows() const;
    const int getCols() const;

    int getZoomStatus() const;
    bool getCameraReset() const;
    Direction getCameraMovement() const;
};

#endif // LEVELOBJECT_H
