#include "compositeinputmanager.h"

CompositeInputManager::CompositeInputManager(QWidget *parent) : InputManager(parent) {}

void CompositeInputManager::addInputManager(InputManager* im)
{
    this->children.push_back(im);
}

std::set<GameInput> CompositeInputManager::popInputs() {
    std::set<GameInput> out;
    for(auto& child : this->children) {
        out.merge(child->popInputs());
    }
    return out;
}
