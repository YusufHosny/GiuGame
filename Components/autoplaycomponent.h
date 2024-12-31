#ifndef AUTOPLAYCOMPONENT_H
#define AUTOPLAYCOMPONENT_H

#include "gameobjectcomponent.h"

class LevelObject;

class AutoPlayComponent : public GameObjectComponent
{
public:
    AutoPlayComponent();

    void toggleAutoplay();

    void step_component(GameObject& owner) override;

private:
    bool active;
};

#endif // AUTOPLAYCOMPONENT_H
