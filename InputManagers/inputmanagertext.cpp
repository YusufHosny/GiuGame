#include "inputmanagertext.h"
#include <QBoxLayout>

InputManagerText::InputManagerText(QWidget *parent) : InputManager(parent) {

    this->inputMap.emplace("pmov", GameInputType::PLAYERMOVE);
    this->inputMap.emplace("goto", GameInputType::GOTO);
    this->inputMap.emplace("auto", GameInputType::AUTOPLAY);
    this->inputMap.emplace("cmov", GameInputType::CAMERAMOVE);
    this->inputMap.emplace("crst", GameInputType::RESETCAMERA);
    this->inputMap.emplace("zoom", GameInputType::ZOOM);

    this->textBar = new TextInputBar(parent);

    connect(textBar, SIGNAL(inputText(QString)), this, SLOT(tryInput(QString)));

}

TextInputBar* InputManagerText::getTextBar() const {
    return this->textBar;
}

void InputManagerText::tryInput(QString in) {
    // split opcode and parameter
    QStringList sl = in.split(" ", Qt::SkipEmptyParts);

    QString stringOpcode, stringParameter;
    if(sl.length() == 1) {
        stringOpcode = sl.at(0);
        stringParameter = "0";
    }
    else if(sl.length() == 2) {
        stringOpcode = sl.at(0);
        stringParameter = sl.at(1);
    }
    else {
        return; // invalid (not structured as opcode + param)
    }

    // get correct operation
    GameInputType operation;
    bool found = false;
    for(auto& entry : inputMap) {
        QString opcode = entry.first;
        if(opcode.contains(stringOpcode, Qt::CaseInsensitive)) {
            operation = entry.second;
            found = true;
        }
    }
    if(!found) return; // invalid (no matching operation)

    // parse parameter
    unsigned int parameter;
    switch(operation) { // special parsing rules
    case GameInputType::PLAYERMOVE:
    case GameInputType::CAMERAMOVE:
        if(QString("up").contains(stringParameter, Qt::CaseInsensitive)) {
            parameter = Direction::UP;
        }
        else if(QString("down").contains(stringParameter, Qt::CaseInsensitive)) {
            parameter = Direction::DOWN;
        }
        else if(QString("left").contains(stringParameter, Qt::CaseInsensitive)) {
            parameter = Direction::LEFT;
        }
        else if(QString("right").contains(stringParameter, Qt::CaseInsensitive)) {
            parameter = Direction::RIGHT;
        }
        break;
    case GameInputType::ZOOM:
        if(QString("in").contains(stringParameter, Qt::CaseInsensitive)) {
            parameter = 0;
        }
        else if(QString("out").contains(stringParameter, Qt::CaseInsensitive)) {
            parameter = 1;
        }
        break;

    default: {
        bool ok;
        parameter = stringParameter.toUInt(&ok);
        if(!ok) return; // invalid (failed to convert to int)
        break;
    }
    }

    this->inputs.emplace(operation, parameter);
}

TextInputBar::TextInputBar(QWidget *parent) : QWidget(parent)
{
    this->textBox = new QLineEdit(this);
    this->textBox->setPlaceholderText("woppa");
    this->submitButton = new QPushButton("Submit", this);

    this->setLayout(new QBoxLayout(QBoxLayout::LeftToRight, this));

    this->layout()->addWidget(this->textBox);
    this->layout()->addWidget(this->submitButton);

    connect(submitButton, SIGNAL(clicked(bool)), this, SLOT(submit()));
    connect(textBox, SIGNAL(returnPressed()), this, SLOT(submit()));

}

void TextInputBar::submit()
{
    emit inputText(this->textBox->text());
}
