#include "gameobject.h"
#include "idgenerator.h"
#include "gameobjectcomponent.h"

GameObject::GameObject(): id(IdGenerator::generateId()) {}

GameObject::GameObject(const std::string label): id(IdGenerator::generateId()), label(label) {}

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


void GameObject::init_impl() {
    // TODO any default gameobject initializatons
    this->init();
    for(auto &child: this->children) {
        child->init_impl();
    }
}
void GameObject::step_impl(qint64 deltaT, std::set<GameInput> inputs) {
    // TODO any default gameobject updates
    this->step(deltaT, inputs);
    for(auto &child: this->children) {
        child->step_impl(deltaT, inputs);
    }

    for(auto &component: this->components) {
        if(component->isActive())
            component->step_component(*this);
    }
}

// hierarchy functionality
void GameObject::addChild(std::shared_ptr<GameObject> child) {
    this->children.push_back(child);
    child->setParent(shared_from_this());
}
void GameObject::removeChild(std::shared_ptr<GameObject> child) {
    std::erase(this->children, child);
    child->parent = nullptr;
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

std::vector<std::shared_ptr<GameObject>> GameObject::childrenWhere(std::predicate<std::shared_ptr<GameObject>> auto pred) const {
    std::vector<std::shared_ptr<GameObject>> out = std::vector<std::shared_ptr<GameObject>>();

    for(auto &child: this->children) {
        if(pred(child)) out.push_back(child);
    }

    return out;
}


