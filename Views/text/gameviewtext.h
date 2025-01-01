#ifndef GAMEVIEWTEXT_H
#define GAMEVIEWTEXT_H

#include "gameview2d.h"

class GameViewText:  public GameView2d
{

public:
    GameViewText(QWidget *parent, std::shared_ptr<const GameObject> state);
};



#endif // GAMEVIEWTEXT_H
