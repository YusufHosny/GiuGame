#ifndef SPRITELOADER_H
#define SPRITELOADER_H

#include <QPixmap>
#include <QString>

class SpriteLoader
{
public:
    SpriteLoader() = delete;

    static std::vector<QPixmap> load(QString path, bool flipped = false);
    static QPixmap flipped(QPixmap in);
};

#endif // SPRITELOADER_H
