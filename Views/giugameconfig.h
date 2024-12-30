#ifndef GIUGAMECONFIG_H
#define GIUGAMECONFIG_H

#include <QString>

namespace GiuGameConfig {

    inline QString startLevelPath = ":img/test.png";

    static int gameWidth = 1200;
    static int gameHeight = 800;

    static qint64 poisonCooldown = 1000; // in msec
    static qint64 movementCooldown = 200; // in msec


    namespace config2d
    {
        static int tileSideLen = 50;  // base tile side length
        static int zoomSpeed = 1; // zoom in/out speed
    };

}


#endif // GIUGAMECONFIG_H
