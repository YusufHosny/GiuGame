#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <qstring.h>
#include "GameObject.h"

class GameLoader
{
public:
    GameLoader() {};

    virtual std::shared_ptr<GameObject> load(QString filepath) = 0;
};

#endif // GAMELOADER_H
