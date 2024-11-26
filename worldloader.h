#ifndef WORLDLOADER_H
#define WORLDLOADER_H

#include "levelobject.h"
#include <qstring.h>
#include <memory>

class WorldLoader
{
public:
    WorldLoader();

    std::shared_ptr<LevelObject> load(QString filepath);
};

#endif // WORLDLOADER_H
