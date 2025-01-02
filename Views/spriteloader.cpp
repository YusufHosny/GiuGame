#include "spriteloader.h"
#include "giugameconfig.h"
#include <iostream>

SpriteLoader::SpriteLoader() {}

std::vector<QPixmap> SpriteLoader::load(QString path, bool flipped)
{
    std::vector<QPixmap> out;
    QPixmap spritesheet = QPixmap(path);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
    int frameCnt = spritesheet.size().width() / tileSideLen;
    std::cout << path.toStdString() << "fc: " << frameCnt << std::endl;

    for(int i = 0; i < frameCnt; i++) {
        QPixmap sprite = spritesheet.copy(i*tileSideLen, 0, tileSideLen, tileSideLen);
        if(flipped)
            out.emplace_back(SpriteLoader::flipped(sprite));
        else
            out.emplace_back(sprite);
    }

    return out;
}

QPixmap SpriteLoader::flipped(QPixmap in)
{
    return in.transformed(QTransform().scale(-1, 1));
}
