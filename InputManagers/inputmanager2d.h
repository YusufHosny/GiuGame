#ifndef INPUTMANAGER2D_H
#define INPUTMANAGER2D_H

#include <QObject>
#include "inputmanager.h"

class InputManager2d : public InputManager
{
    Q_OBJECT
public:
    InputManager2d(QWidget *parent);

private:
    // event handlers
    bool eventFilter(QObject *o, QEvent *e) override;
};

#endif // INPUTMANAGER2D_H
