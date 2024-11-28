#ifndef WORLDLOADER_H
#define WORLDLOADER_H

#include "gameloader.h"
#include <qstring.h>
#include <memory>

class WorldLoader : public GameLoader
{
public:
    WorldLoader();

    std::shared_ptr<GameObject> load(QString filepath) override;
};

#endif // WORLDLOADER_H
