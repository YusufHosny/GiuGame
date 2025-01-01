#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <qstring.h>
#include "gameobject.h"

class GameLoader
{
protected:
    GameLoader() {};

public:
    virtual ~GameLoader() {};

    virtual std::shared_ptr<GameObject> load(QString filepath) = 0;
};

#endif // GAMELOADER_H
