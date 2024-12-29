#include "inputmanager2d.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include "GameInput.h"
#include <iostream>

InputManager2d::InputManager2d(QWidget *parent) : InputManager(parent) {}

bool InputManager2d::eventFilter(QObject *o, QEvent *e) {
    if(e->type() == QEvent::MouseButtonPress) {
        auto me = dynamic_cast<QMouseEvent*>(e);
        if(me->button() == Qt::MouseButton::LeftButton) {
            inputs.insert(GameInput(GameInputType::GOTO));
        }
        else if(me->button() == Qt::MouseButton::RightButton) {
            inputs.insert(GameInput(GameInputType::SWITCHVIEW, 1));
        }
        else if(me->button() == Qt::MouseButton::MiddleButton) {
            inputs.insert(GameInput(GameInputType::SWITCHVIEW, 2));
        }
    }
    else if(e->type() == QEvent::KeyPress) {
        auto ke = dynamic_cast<QKeyEvent*>(e);
        switch(ke->key()) {
        case Qt::Key_W: {
            inputs.insert(GameInput(GameInputType::PLAYERMOVE, 0));
            break;
        }

        case Qt::Key_A: {
            inputs.insert(GameInput(GameInputType::PLAYERMOVE, 2));
            break;
        }

        case Qt::Key_S: {
            inputs.insert(GameInput(GameInputType::PLAYERMOVE, 1));
            break;
        }

        case Qt::Key_D: {
            inputs.insert(GameInput(GameInputType::PLAYERMOVE, 3));
            break;
        }
        }
    }
    else if(e->type() == QEvent::Wheel) {
        auto we = dynamic_cast<QWheelEvent*>(e);

        if(we->angleDelta().y() > 0) {
            inputs.insert(GameInput(GameInputType::ZOOM, 0));
        }
        else {
            inputs.insert(GameInput(GameInputType::ZOOM, 1));
        }
    }
    else {
        return false;
    }

    return true;
};
