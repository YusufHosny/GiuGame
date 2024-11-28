#include "GameObject.h"
#include "IdGenerator.h"

GameObject::GameObject(const std::string label): id(IdGenerator::generateId()) {}


void GameObject::setParent(std::shared_ptr<GameObject> parent) {
    this->parent = parent;
}

std::shared_ptr<GameObject> GameObject::getParent() const {
    return this->parent;
}

bool GameObject::hasParent() const {
    return this->parent != nullptr;
}


std::ostream& operator<<(std::ostream& os, GameObject& s) {
    os << s.dumpData();
    return os;
}


void GameObject::init() {
    // TODO any default gameobject initializatons
}
void GameObject::step(qint64 deltaT, std::set<GameInput> inputs) {
    // TODO any default gameobject updates
}

// hierarchy functionality
void GameObject::addChild(std::shared_ptr<GameObject> child) {
    this->children.push_back(child);
}
void GameObject::removeChild(std::shared_ptr<GameObject> child) {
    std::erase(this->children, child);
}

unsigned int GameObject::getId() const {
    return this->id;
}
std::string GameObject::getLabel() const {
    return this->label;
}


std::shared_ptr<GameObject> GameObject::get(const unsigned int index) const {
    return this->children.at(index);
}
std::shared_ptr<GameObject> GameObject::operator[](int index) const {
    return this->children[index];
}

std::vector<std::shared_ptr<GameObject>> GameObject::childrenWhere(std::predicate<GameObject> auto pred) const {
    std::vector<std::shared_ptr<GameObject>> out = std::vector<std::shared_ptr<GameObject>>();

    for(auto &gameObject: this->children) {
        if(pred(gameObject)) out.push_back(gameObject);
    }

    return out;
}


