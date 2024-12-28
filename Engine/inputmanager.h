#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <set>
#include <QWidget>
#include "GameInput.h"

class InputManager: public QWidget
{
    Q_OBJECT

protected:
    InputManager(QWidget *parent);

    std::set<GameInput> inputs;

public:
    // virtual in case some specific cleanup or action has to occur in derived classes
    virtual std::set<GameInput> popInputs();
};

#endif // INPUTMANAGER_H
