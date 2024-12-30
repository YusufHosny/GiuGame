#ifndef GIUGAMECONFIG_H
#define GIUGAMECONFIG_H

#include <QString>

class GiuGameConfig {

public:
    static const GiuGameConfig& getInstance();

    static void loadFromFile(QString path);

    GiuGameConfig(GiuGameConfig const&) = delete;
    void operator=(GiuGameConfig const&) = delete;

    class Config2d
    {
    public:
        int tileSideLen;  // base tile side length
        float zoomSpeed; // zoom in/out speed
    };

    QString startLevelPath;

    int gameWidth;
    int gameHeight;

    qint64 poisonCooldown; // in msec
    qint64 movementCooldown;; // in msec

    Config2d config2d;

private:
    GiuGameConfig();
};


#endif // GIUGAMECONFIG_H
