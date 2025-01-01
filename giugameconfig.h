#ifndef GIUGAMECONFIG_H
#define GIUGAMECONFIG_H

#include <QString>
#include <QColor>
#include <QFont>

enum ViewType {
    VIEW2D, VIEW3D, VIEWTEXT
};

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

    class ConfigText
    {
    public:
        QColor bgColor;
        QFont textFont;
    };

    QString startLevelPath;

    int gameWidth;
    int gameHeight;

    qint64 poisonCooldown; // in msec
    qint64 movementCooldown; // in msec
    qint64 blinkCooldown; // in msec

    Config2d config2d;
    ConfigText configText;

private:
    GiuGameConfig();
};


#endif // GIUGAMECONFIG_H
