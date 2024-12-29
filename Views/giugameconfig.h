#ifndef GIUGAMECONFIG_H
#define GIUGAMECONFIG_H

#include <QString>

namespace GiuGameConfig {

    inline const QString startLevelPath = ":img/worldmap.png";

    namespace config2d
    {
        static const int tileSideLen = 50;  // base tile side length
        static int zoomSpeed = 1; // zoom in/out speed
    };

}


#endif // GIUGAMECONFIG_H
