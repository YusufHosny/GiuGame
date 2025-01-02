#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <memory>
#include <set>
#include <vector>
#include <iostream>
#include <QIntegerForSize>
#include "gameinput.h"
#include "gameobjectcomponent.h"

class GameObject : public std::enable_shared_from_this<GameObject> {

    private:
        GameObject(const GameObject &) = delete;
        GameObject &operator=(const GameObject &) = delete;

    protected:
        const unsigned int id;
        const std::string label;

        std::shared_ptr<GameObject> parent;
        std::vector<std::shared_ptr<GameObject>> children;

        std::vector<std::shared_ptr<GameObjectComponent>> components;

        virtual void init() = 0;
        virtual void step(qint64 deltaT, std::set<GameInput> inputs) = 0;

        GameObject(const std::string label);
        GameObject();


    public:

        virtual ~GameObject() {};

        // gameobject functionality
        void init_impl();
        void step_impl(qint64 deltaT, std::set<GameInput> inputs);

        // hierarchy functionality
        void addChild(std::shared_ptr<GameObject> child);
        void removeChild(std::shared_ptr<GameObject> child);

        unsigned int getId() const;
        std::string getLabel() const;

        template <class T>
        std::shared_ptr<T> findChildById(const unsigned int targetId) const {
            for(auto &child : this->children) {
                if(child->id == targetId) {
                    return std::dynamic_pointer_cast<T>(child);
                }
            }
            return nullptr;
        }

        template <class T>
        std::vector<std::shared_ptr<T>> findChildren() const {
            std::vector<std::shared_ptr<T>> out;

            for(auto &child : this->children) {
                if(auto c = std::dynamic_pointer_cast<T>(child)) {
                    out.push_back(c);
                }
            }

            return out;
        }

        template <class T>
        std::vector<std::shared_ptr<T>> findChildrenByLabel(const std::string targetLabel) const {
            std::vector<std::shared_ptr<T>> out;

            for(auto &child : this->children) {
                if(child->label == targetLabel) {
                    if(auto c = std::dynamic_pointer_cast<T>(child)) {
                        out.push_back(c);
                    }
                }
            }

            return out;
        }

        template <class T>
        std::vector<std::shared_ptr<GameObject>> childrenWithComponent() {
            std::vector<std::shared_ptr<GameObject>> out;

                for(auto &child : this->children) {
                    for(auto &component: child->components) {
                        if( dynamic_cast<T*>(component.get()) ) {
                            out.push_back(child);
                        }
                    }
            }

            return out;

        }

        template <class T>
        std::vector<std::shared_ptr<GameObject>> childrenWithActiveComponent() {
            std::vector<std::shared_ptr<GameObject>> out;

            for(auto &child : this->children) {
                for(auto &component: child->components) {
                    if( dynamic_cast<T*>(component.get()) && component->isActive() ) {
                        out.push_back(child);
                    }
                }
            }

            return out;

        }

        template <class T>
        std::shared_ptr<T> getComponent() {

            for(auto &component: this->components) {
                if( auto c = std::dynamic_pointer_cast<T>(component) ) {
                    return c;
                }
            }
            return nullptr;
        }

        template <class T>
        std::shared_ptr<T> getComponent() const {

            for(auto &component: this->components) {
                if( auto c = std::dynamic_pointer_cast<T>(component) ) {
                    return c;
                }
            }
            return nullptr;
        }

        std::shared_ptr<GameObject> get(const unsigned int index) const;
        std::shared_ptr<GameObject> operator[](int index) const;

        std::vector<std::shared_ptr<GameObject>> childrenWhere(std::predicate<std::shared_ptr<GameObject>> auto pred) const;

        void setParent(std::shared_ptr<GameObject> parent);
        std::shared_ptr<GameObject> getParent() const;
        bool hasParent() const;

        virtual std::string dumpData() const = 0;
        friend std::ostream& operator<<(std::ostream& os, GameObject& s);


};

#endif // GAMEOBJECT_H
