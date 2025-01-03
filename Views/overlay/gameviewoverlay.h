#ifndef GAMEVIEWOVERLAY_H
#define GAMEVIEWOVERLAY_H

#include "gameview2d.h"
#include <QPixmap>

class GameViewOverlay:  public GameView2d
{

public:
    GameViewOverlay(QWidget *parent, std::shared_ptr<const GameObject> state);

private:

    QPixmap overlayImage;

    void drawTiles(std::shared_ptr<const LevelObject> levelObject) override;

};



#endif // GAMEVIEWOVERLAY_H
