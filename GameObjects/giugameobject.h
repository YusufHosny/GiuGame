#ifndef GIUGAMEOBJECT_H
#define GIUGAMEOBJECT_H

#include <gameobject.h>
#include "worldloader.h"

class GiuGameObject : public GameObject
{
public:
    GiuGameObject();

    void nextLevel(QString nextLevelPath);

    void init() override;
    void step(qint64 deltaT, std::set<GameInput> inputs) override;

    std::string dumpData() const override;

private:
    GiuGameObject(const GiuGameObject &) = delete;
    GiuGameObject &operator=(const GiuGameObject &) = delete;

    std::shared_ptr<GameObject> nextLevelObject;
    WorldLoader wl;
};

#endif // GIUGAMEOBJECT_H
