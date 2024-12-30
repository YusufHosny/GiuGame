#ifndef GIUGAMECONFIG_H
#define GIUGAMECONFIG_H

#include <QString>

namespace GiuGameConfig {

    inline QString startLevelPath = ":img/maze1.png";

    static int gameWidth = 1200;
    static int gameHeight = 800;



    namespace config2d
    {
        static int tileSideLen = 50;  // base tile side length
        static int zoomSpeed = 1; // zoom in/out speed
    };

}


#endif // GIUGAMECONFIG_H
