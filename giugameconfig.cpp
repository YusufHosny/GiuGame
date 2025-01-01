#include "giugameconfig.h"

const GiuGameConfig& GiuGameConfig::getInstance() {
    static GiuGameConfig instance;
    return instance;
}

GiuGameConfig::GiuGameConfig() {

    config2d.tileSideLen = 50;  // base tile side length
    config2d.zoomSpeed = 1; // zoom in/out speed

    configText.bgColor = Qt::GlobalColor::black;
    configText.textFont = QFont("Arial", 20);

    startLevelPath = ":img/worldmap.png";

    gameWidth = 1200;
    gameHeight = 800;

    poisonCooldown = 1000; // in msec
    movementCooldown = 200; // in msec
    blinkCooldown = 1000; // in msec

}

void GiuGameConfig::loadFromFile(QString path) {

}
