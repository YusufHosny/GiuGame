#ifndef INPUTMANAGERTEXT_H
#define INPUTMANAGERTEXT_H

#include <QObject>
#include "inputmanager.h"
#include <QLineEdit>
#include <QPushButton>

class TextInputBar : public QWidget {
    Q_OBJECT

public:
    TextInputBar(QWidget* parent);

private:
    QLineEdit* textBox;
    QPushButton* submitButton;

private slots:
    void submit();

signals:
    void inputText(QString text);

};

class InputManagerText : public InputManager
{
    Q_OBJECT
public:
    InputManagerText(QWidget* parent);

    TextInputBar* getTextBar() const;

private:
    std::map<QString, GameInputType> inputMap;
    TextInputBar* textBar;

private slots:
    void tryInput(QString in);

};




#endif // INPUTMANAGERTEXT_H
