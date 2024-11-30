#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QWidget>
#include "GameObject.h"


class GameView: public QWidget
{
    Q_OBJECT

public:

    virtual void draw(std::shared_ptr<const GameObject> state) = 0;
};

#endif // GAMEVIEW_H
