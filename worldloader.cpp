#include "worldloader.h"
#include "world.h"
#include "levelobject.h"
#include "playerobject.h"
#include "enemyobject.h"
#include "benemyobject.h"
#include "penemyobject.h"
#include "healthpackobject.h"
#include "doorobject.h"
#include "giugameconfig.h"
#include <memory>
#include <QFile>
#include <QTextStream>

WorldLoader::WorldLoader() {}

std::shared_ptr<GameObject> WorldLoader::load(QString level)
{
    const GiuGameConfig& config = GiuGameConfig::getInstance();

    // load configs and assign default values
    unsigned int enemies = 4, hpacks = 4;
    float pratio = .2, bratio = .2;
    unsigned int xStart = 0, yStart = 0;
    unsigned int xEnd = 0, yEnd = 0;
    QString nextLevel = "";

    // load config file
    try {
        QFile file(config.levelPathPrefix + level  + "/config.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) throw;

        bool ok;
        QTextStream in(&file);
        QList<QString> levelConfig = in.readLine().split(",");
        enemies = levelConfig.at(0).toUInt(&ok); if(!ok) throw;
        hpacks = levelConfig.at(1).toUInt(&ok); if(!ok) throw;
        pratio = levelConfig.at(2).toFloat(&ok); if(!ok) throw;
        bratio = levelConfig.at(3).toFloat(&ok); if(!ok) throw;
        QList<QString> startConfig = in.readLine().split(","); if(!ok) throw;
        xStart = startConfig.at(0).toUInt(&ok); if(!ok) throw;
        yStart = startConfig.at(1).toUInt(&ok); if(!ok) throw;
        QList<QString> endConfig = in.readLine().split(","); if(!ok) throw;
        xEnd = endConfig.at(0).toUInt(&ok); if(!ok) throw;
        yEnd = endConfig.at(1).toUInt(&ok); if(!ok) throw;
        nextLevel = endConfig.at(2);
    }
    catch (...) {
        // set defaults
        enemies = 4;
        hpacks = 4;
        pratio = .2;
        bratio = .2;
        xStart = 0;
        yStart = 0;
        xEnd = 0;
        yEnd = 0;
        nextLevel = "";
    }

    // load data
    World wrld;
    wrld.createWorld(config.levelPathPrefix + level + "/data.png", enemies, hpacks, pratio);

    // create level object
    int c = wrld.getCols();
    int r = wrld.getRows();
    std::shared_ptr<LevelObject> levelObject =
        std::shared_ptr<LevelObject>( new LevelObject(wrld.getTiles(), r, c, config.levelPathPrefix + level + "/overlay.png") );

    // create health packs
    std::vector<std::unique_ptr<Tile>> healthPacks = wrld.getHealthPacks();
    for(auto &hp: healthPacks) {
        std::shared_ptr<HealthPackObject> healthPackObject =
            std::shared_ptr<HealthPackObject>( new HealthPackObject(std::move(hp)) );
        levelObject->addChild(healthPackObject);
    }

    // create player object
    auto protag = wrld.getProtagonist();
    protag->setPos(xStart, yStart);
    std::shared_ptr<PlayerObject> playerObject =
        std::shared_ptr<PlayerObject>( new PlayerObject(std::move(protag)) );
    levelObject->addChild(playerObject);

    // create enemy objects
    std::vector<std::unique_ptr<Enemy>> enemyModels = wrld.getEnemies();
    std::vector<std::unique_ptr<Enemy>> enemyModelsLeft;
    for(auto &enemy: enemyModels) {
        // check if enemy is a penemy or a normal enemy
        if( dynamic_cast<PEnemy*>(enemy.get()) ) {
            std::shared_ptr<PEnemyObject> pEnemyObject = std::shared_ptr<PEnemyObject>( new PEnemyObject(std::unique_ptr<PEnemy>( dynamic_cast<PEnemy*>(enemy.release()) )) );
            levelObject->addChild(pEnemyObject);
        }
        else {
            enemyModelsLeft.push_back(std::move(enemy));
        }
    }
    unsigned int bCount = static_cast<int>(bratio * enemyModelsLeft.size());
    unsigned int i;
    for(auto &enemy: enemyModelsLeft) {
        if( i < bCount ) {
            std::shared_ptr<BEnemyObject> bEnemyObject = std::shared_ptr<BEnemyObject>( new BEnemyObject(std::move(enemy)) );
            levelObject->addChild(bEnemyObject);
        }
        else {
            std::shared_ptr<EnemyObject> enemyObject = std::shared_ptr<EnemyObject>( new EnemyObject(std::move(enemy)) );
            levelObject->addChild(enemyObject);
        }
        i++;
    }


    // add door object
    if(!nextLevel.isEmpty())
        levelObject->addChild(std::shared_ptr<DoorObject>( new DoorObject(nextLevel, xEnd, yEnd) ));

    return levelObject;
}
