#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <set>
#include <QWidget>
#include "gameinput.h"

class InputManager: public QWidget
{
    Q_OBJECT

protected:
    InputManager(QWidget *parent);

    std::set<GameInput> inputs;

public:
    virtual ~InputManager() {};

    virtual std::set<GameInput> popInputs();
};

#endif // INPUTMANAGER_H
