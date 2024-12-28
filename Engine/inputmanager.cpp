#include "inputmanager.h"

InputManager::InputManager(QWidget *parent) : QWidget(parent) {}

std::set<GameInput> InputManager::popInputs() {
    auto copy = this->inputs;
    this->inputs.clear();
    return copy;
}
