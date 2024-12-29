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

    int zoomStatus; // -1: zoom in, 0: no change, 1: zoom out
    bool cameraReset;

    LevelObject(std::vector<std::unique_ptr<Tile>> tiles, int rows, int cols);
    int cols, rows;

public:
    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

    friend class WorldLoader;

    const std::vector<std::unique_ptr<Tile>> &getTiles() const {return tiles;}
    const std::unique_ptr<Tile> &getTile(int x, int y) {return tiles.at(y*cols + x);}

    const int getRows() const {return rows;}
    const int getCols() const {return cols;}

    int getZoomStatus() const {return zoomStatus;}
    bool getCameraReset() const {return cameraReset;}
};

#endif // LEVELOBJECT_H
