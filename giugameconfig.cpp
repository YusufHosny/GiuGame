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

    config3d.cameraFOV = 120; // degrees fov
    config3d.cameraZ = 2*config2d.tileSideLen;
    config3d.nearPlane = 10;
    config3d.farPlane = 12*config2d.tileSideLen;

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
