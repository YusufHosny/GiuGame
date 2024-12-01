#include "PlayerView2D.h"
#include <QPainter>
#include "playerobject.h"

PlayerView2D::PlayerView2D(QGraphicsItem *parent) : QGraphicsItem(parent)  {}

void PlayerView2D::draw(std::shared_ptr<const GameObject> go) {

    auto playerObject = std::dynamic_pointer_cast<PlayerObject>(go);
    if (!playerObject) return;
    float x = playerObject->getProtagonist().getXPos();
    float y = playerObject->getProtagonist().getYPos();
    // Trigger a repaint
    QGraphicsItem::update();
}


