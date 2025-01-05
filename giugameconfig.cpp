#include "giugameconfig.h"

const GiuGameConfig& GiuGameConfig::getInstance() {
    static GiuGameConfig instance;
    return instance;
}

GiuGameConfig::GiuGameConfig() {

    config2d.tileSideLen = 32;
    config2d.zoomSpeed = 1;
    config2d.panSpeed = 10;

    configText.bgColor = Qt::GlobalColor::black;
    configText.textFont = QFont("Arial", 20);

    levelPathPrefix = ":/levels/";
    startLevel = "1";

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
