#include "worldloader.h"
#include "world.h"
#include "levelobject.h"
#include "playerobject.h"
#include "enemyobject.h"
#include "benemyobject.h"
#include "penemyobject.h"
#include "healthpackobject.h"
#include "doorobject.h"
#include <memory>

WorldLoader::WorldLoader() {}

std::shared_ptr<GameObject> WorldLoader::load(QString filepath)
{
    World wrld;
    wrld.createWorld(filepath, 4, 2);

    // create level object
    int c = wrld.getCols();
    int r = wrld.getRows();
    std::shared_ptr<LevelObject> levelObject =
        std::shared_ptr<LevelObject>( new LevelObject(wrld.getTiles(), r, c) );

    // create health packs
    std::vector<std::unique_ptr<Tile>> healthPacks = wrld.getHealthPacks();
    for(auto &hp: healthPacks) {
        std::shared_ptr<HealthPackObject> healthPackObject =
            std::shared_ptr<HealthPackObject>( new HealthPackObject(std::move(hp)) );
        levelObject->addChild(healthPackObject);
    }

    // create player object
    std::shared_ptr<PlayerObject> playerObject =
        std::shared_ptr<PlayerObject>( new PlayerObject(wrld.getProtagonist()) );
    levelObject->addChild(playerObject);

    // create enemy objects
    std::vector<std::unique_ptr<Enemy>> enemyModels = wrld.getEnemies();
    bool alternate = false;
    for(auto &enemy: enemyModels) {
        // check if enemy is a penemy or a normal enemy
        if( dynamic_cast<PEnemy*>(enemy.get()) ) {
            std::shared_ptr<PEnemyObject> pEnemyObject = std::shared_ptr<PEnemyObject>( new PEnemyObject(std::unique_ptr<PEnemy>( dynamic_cast<PEnemy*>(enemy.release()) )) );
            levelObject->addChild(pEnemyObject);
        }
        else {
            if(alternate) {
                std::shared_ptr<EnemyObject> enemyObject = std::shared_ptr<EnemyObject>( new EnemyObject(std::move(enemy)) );
                levelObject->addChild(enemyObject);
            }
            else {
                std::shared_ptr<BEnemyObject> enemyObject = std::shared_ptr<BEnemyObject>( new BEnemyObject(std::move(enemy)) );
                levelObject->addChild(enemyObject);
            }
            alternate = !alternate;
        }
    }


    // add door object
    levelObject->addChild(std::shared_ptr<DoorObject>( new DoorObject(":/img/maze1.png", c-1, r-1) ));

    return levelObject;
}
