#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QWidget>
#include "levelobject.h"


class GameView: public QWidget
{
    Q_OBJECT
public:
    GameView();

    virtual void draw(std::shared_ptr<const LevelObject> state);
};

#endif // GAMEVIEW_H
