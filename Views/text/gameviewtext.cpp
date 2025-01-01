#include "gameviewtext.h"

GameViewText::GameViewText(QWidget *parent, std::shared_ptr<const GameObject> state) : GameView2d(parent, state, ViewType::VIEWTEXT) {}
