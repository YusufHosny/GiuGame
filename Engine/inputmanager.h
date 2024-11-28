#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <set>
#include <QObject>
#include "GameInput.h"

class InputManager: public QObject
{
    Q_OBJECT

private:
    std::set<GameInput> inputs;

public:
    InputManager();

    // virtual in case some specific cleanup or action has to occur in derived classes
    virtual std::set<GameInput> popInputs();
};

#endif // INPUTMANAGER_H
