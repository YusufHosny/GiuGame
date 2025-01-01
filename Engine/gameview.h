#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "gameobject.h"

class GameView
{
protected:
    GameView() {};

public:
    virtual ~GameView() {};

    virtual void draw(std::shared_ptr<const GameObject> state) = 0;
};

#endif // GAMEVIEW_H
