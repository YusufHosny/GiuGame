#include "worldloader.h"
#include "world.h"
#include "levelobject.h"
#include "playerobject.h"
#include "enemyobject.h"
#include "penemyobject.h"

WorldLoader::WorldLoader() {}

std::shared_ptr<GameObject> WorldLoader::load(QString filepath)
{
    World wrld;
    wrld.createWorld(filepath,1, 1);

    // create level object
    int c = wrld.getCols();
    int r = wrld.getRows();
    std::shared_ptr<LevelObject> levelObject =
        std::make_shared<LevelObject>(wrld.getTiles(), wrld.getHealthPacks(), r, c);

    // create player object
    std::shared_ptr<PlayerObject> playerObject =
        std::make_shared<PlayerObject>(wrld.getProtagonist());
    levelObject->addChild(playerObject);

    // create enemy objects
    std::vector<std::unique_ptr<Enemy>> enemyModels = wrld.getEnemies();
    for(auto &enemy: enemyModels) {
        // check if enemy is a penemy or a normal enemy
        if( dynamic_cast<PEnemy*>(enemy.get()) ) {
            std::shared_ptr<PEnemyObject> pEnemyObject = std::make_shared<PEnemyObject>(std::move(enemy));
            levelObject->addChild(pEnemyObject);
        }
        else {
            std::shared_ptr<EnemyObject> enemyObject = std::make_shared<EnemyObject>(std::move(enemy));
            levelObject->addChild(enemyObject);
        }
    }

    return levelObject;
}
