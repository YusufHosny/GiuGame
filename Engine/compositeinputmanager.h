#ifndef COMPOSITEINPUTMANAGER_H
#define COMPOSITEINPUTMANAGER_H

#include "inputmanager.h"

class CompositeInputManager : public InputManager
{

private:
    std::vector<InputManager*> children;

public:
    CompositeInputManager(QWidget *parent);

    void addInputManager(InputManager* im);

    std::set<GameInput> popInputs() override;
};

#endif // COMPOSITEINPUTMANAGER_H
