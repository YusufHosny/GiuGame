#ifndef GIUGAMECONFIG_H
#define GIUGAMECONFIG_H

#include <QString>
#include <QColor>
#include <QFont>

enum ViewType {
    VIEW2D, VIEW3D, VIEWTEXT, VIEWOVERLAY
};

class GiuGameConfig {

public:
    static const GiuGameConfig& getInstance();

    GiuGameConfig(GiuGameConfig const&) = delete;
    void operator=(GiuGameConfig const&) = delete;

    class Config2d
    {
    public:
        int tileSideLen;  // base tile side length
        float zoomSpeed; // zoom in/out speed
        float panSpeed; // panning speed
    };

    class ConfigText
    {
    public:
        QColor bgColor;
        QFont textFont;
    };

    class Config3d {
    public:
        float cameraZ;
        float cameraFOV;
        float nearPlane, farPlane;
    };

    QString levelPathPrefix;
    QString startLevel;

    int gameWidth;
    int gameHeight;

    // in msec
    qint64 poisonCooldown;
    qint64 movementCooldown;
    qint64 blinkCooldown;
    qint64 pathOpacDecayCooldown;

    float pathBaseOpacity;
    float pathOpacityDecay;

    Config2d config2d;
    ConfigText configText;
    Config3d config3d;

private:
    GiuGameConfig();
};


#endif // GIUGAMECONFIG_H
