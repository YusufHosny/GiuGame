#include "inputmanager.h"

InputManager::InputManager() {}

std::set<GameInput> InputManager::popInputs() {
    auto copy = this->inputs;
    this->inputs.clear();
    return copy;
}
