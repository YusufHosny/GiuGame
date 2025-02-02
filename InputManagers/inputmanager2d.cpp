#include "inputmanager2d.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include "gameinput.h"
#include "gameview2d.h"
#include "giugameconfig.h"
#include <iostream>

InputManager2d::InputManager2d(QWidget *parent) : InputManager(parent) {}

bool InputManager2d::eventFilter(QObject *o, QEvent *e) {
    if(e->type() == QEvent::MouseButtonPress) {
        auto me = dynamic_cast<QMouseEvent*>(e);
        if(me->button() == Qt::MouseButton::LeftButton) {
            if(auto gv = dynamic_cast<GameView2d*>(o)) {
                auto pos = gv->mapToScene(static_cast<QMouseEvent*>(e)->pos()).toPoint();
                int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
                int param = (pos.x()/tileSideLen + pos.y()/tileSideLen*gv->getCols()) ;
                inputs.insert(GameInput(GameInputType::GOTO, param));
            }
        }
        else if(me->button() == Qt::MouseButton::RightButton) {
            inputs.insert(GameInput(GameInputType::AUTOPLAY));
        }
        else if(me->button() == Qt::MouseButton::MiddleButton) {
            std::cout << "mmbutton not used yet" << std::endl;
        }
    }
    else if(e->type() == QEvent::KeyPress) {
        auto ke = dynamic_cast<QKeyEvent*>(e);
        switch(ke->key()) {
        case Qt::Key_W: {
            inputs.insert(GameInput(GameInputType::PLAYERMOVE, Direction::UP));
            break;
        }

        case Qt::Key_A: {
            inputs.insert(GameInput(GameInputType::PLAYERMOVE, Direction::LEFT));
            break;
        }

        case Qt::Key_S: {
            inputs.insert(GameInput(GameInputType::PLAYERMOVE, Direction::DOWN));
            break;
        }

        case Qt::Key_D: {
            inputs.insert(GameInput(GameInputType::PLAYERMOVE, Direction::RIGHT));
            break;
        }

        case Qt::Key_Up: {
            inputs.insert(GameInput(GameInputType::CAMERAMOVE, Direction::UP));
            break;
        }

        case Qt::Key_Down: {
            inputs.insert(GameInput(GameInputType::CAMERAMOVE, Direction::DOWN));
            break;
        }

        case Qt::Key_Left: {
            inputs.insert(GameInput(GameInputType::CAMERAMOVE, Direction::LEFT));
            break;
        }

        case Qt::Key_Right: {
            inputs.insert(GameInput(GameInputType::CAMERAMOVE, Direction::RIGHT));
            break;
        }

        case Qt::Key_R: {
            inputs.insert(GameInput(GameInputType::RESETCAMERA));
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

