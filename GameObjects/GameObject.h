#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>
#include <memory>
#include <set>
#include <vector>
#include <iostream>
#include <QIntegerForSize>
#include "GameInput.h"

class GameObject {

    private:
        GameObject(const GameObject &) = delete;
        GameObject &operator=(const GameObject &) = delete;


    protected:
        const unsigned int id;
        const std::string label;

        std::shared_ptr<GameObject> parent;
        std::vector<std::shared_ptr<GameObject>> children;

        GameObject(const std::string label);
        GameObject();


    public:

        virtual ~GameObject() {};

        // gameobject functionality
        // for these functions, basic implemetation for all GOs
        // called in inherited classes as GameObject::init() etc
        virtual void init();
        virtual void step(qint64 deltaT, std::set<GameInput> inputs);

        // hierarchy functionality
        void addChild(std::shared_ptr<GameObject> child);
        void removeChild(std::shared_ptr<GameObject> child);

        unsigned int getId() const;
        std::string getLabel() const;

        template <class T>
        std::shared_ptr<T> findChildById(const unsigned int targetId) const {
            for(auto &child : this->children) {
                if(child->id == targetId) {
                    return dynamic_cast<T>(child);
                }
            }
            return nullptr;
        }

        template <class T>
        std::vector<std::shared_ptr<T>> findChildren() const {
            std::vector<std::shared_ptr<T>> out;

            for(auto &child : this->children) {
                if(auto c = dynamic_cast<T>(child)) {
                    out.push_back(c);
                }
            }

            return out;
        }

        template <class T>
        std::vector<std::shared_ptr<T>> findChildrenByLabel(const std::string targetLabel) const {
            std::vector<std::shared_ptr<T>> out;
            \
            for(auto &child : this->children) {
                if(child->label == targetLabel) {
                    if(auto c = dynamic_cast<T>(child)) {
                        out.push_back(c);
                    }
                }
            }

            return out;
        }

        std::shared_ptr<GameObject> get(const unsigned int index) const;
        std::shared_ptr<GameObject> operator[](int index) const;

        std::vector<std::shared_ptr<GameObject>> childrenWhere(std::predicate<GameObject> auto pred) const;

        void setParent(std::shared_ptr<GameObject> parent);
        std::shared_ptr<GameObject> getParent() const;
        bool hasParent() const;

        virtual std::string dumpData() const = 0;
        friend std::ostream& operator<<(std::ostream& os, GameObject& s);


};

#endif // GAMEOBJECT_HPP
