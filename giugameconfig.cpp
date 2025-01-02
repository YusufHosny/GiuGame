#include "giugameconfig.h"

const GiuGameConfig& GiuGameConfig::getInstance() {
    static GiuGameConfig instance;
    return instance;
}

GiuGameConfig::GiuGameConfig() {

    config2d.tileSideLen = 32;  // base tile side length
    config2d.zoomSpeed = 1; // zoom in/out speed

    configText.bgColor = Qt::GlobalColor::black;
    configText.textFont = QFont("Arial", 20);

    startLevelPath = ":img/worldmap.png";

    gameWidth = 1200;
    gameHeight = 800;

    poisonCooldown = 1000;
    movementCooldown = 200;
    blinkCooldown = 1000;
    pathOpacDecayCooldown = 100;

    pathBaseOpacity = .9;
    pathOpacityDecay = .01;

}

void GiuGameConfig::loadFromFile(QString path) {

}
