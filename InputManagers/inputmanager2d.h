#ifndef INPUTMANAGER2D_H
#define INPUTMANAGER2D_H

#include <QObject>
#include "inputmanager.h"

class InputManager2d : public InputManager
{
    Q_OBJECT
public:
    InputManager2d();

private:
    // event handlers
    void mousePressEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
};

#endif // INPUTMANAGER2D_H
