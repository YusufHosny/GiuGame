#include "worldloader.h"
#include "world.h"
#include "levelobject.h"
#include "playerobject.h"
#include "enemyobject.h"
#include "penemyobject.h"
#include <memory>

WorldLoader::WorldLoader() {}

std::shared_ptr<GameObject> WorldLoader::load(QString filepath)
{
    World wrld;
    wrld.createWorld(filepath,1, 1);

    // create level object
    int c = wrld.getCols();
    int r = wrld.getRows();
    std::shared_ptr<LevelObject> levelObject =
        std::shared_ptr<LevelObject>( new LevelObject(wrld.getTiles(), wrld.getHealthPacks(), r, c) );

    // create player object
    std::shared_ptr<PlayerObject> playerObject =
        std::shared_ptr<PlayerObject>( new PlayerObject(wrld.getProtagonist()) );
    levelObject->addChild(playerObject);

    // create enemy objects
    std::vector<std::unique_ptr<Enemy>> enemyModels = wrld.getEnemies();
    for(auto &enemy: enemyModels) {
        // check if enemy is a penemy or a normal enemy
        if( dynamic_cast<PEnemy*>(enemy.get()) ) {
            std::shared_ptr<PEnemyObject> pEnemyObject = std::shared_ptr<PEnemyObject>( new PEnemyObject(std::unique_ptr<PEnemy>( dynamic_cast<PEnemy*>(enemy.release()) )) );
            levelObject->addChild(pEnemyObject);
        }
        else {
            std::shared_ptr<EnemyObject> enemyObject = std::shared_ptr<EnemyObject>( new EnemyObject(std::move(enemy)) );
            levelObject->addChild(enemyObject);
        }
    }

    return levelObject;
}
