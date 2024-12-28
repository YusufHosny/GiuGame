#include "inputmanager2d.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include "GameInput.h"


InputManager2d::InputManager2d() {}


void InputManager2d::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::MouseButton::LeftButton) {
        inputs.insert(GameInput(GameInputType::GOTO));
    }
    else {
        inputs.insert(GameInput(GameInputType::SWITCHVIEW3D));
    }

}

void InputManager2d::wheelEvent(QWheelEvent *e) {
    if(e->angleDelta().y() > 0) {
        inputs.insert(GameInput(GameInputType::ZOOMIN));
    }
    else {
        inputs.insert(GameInput(GameInputType::ZOOMOUT));
    }

}


void InputManager2d::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {

    case Qt::Key_W:
        inputs.insert(GameInput(GameInputType::PLAYERUP));
        break;

    case Qt::Key_A:
        inputs.insert(GameInput(GameInputType::PLAYERLEFT));
        break;

    case Qt::Key_S:
        inputs.insert(GameInput(GameInputType::PLAYERDOWN));
        break;

    case Qt::Key_D:
        inputs.insert(GameInput(GameInputType::PLAYERRIGHT));
        break;

    }
}
