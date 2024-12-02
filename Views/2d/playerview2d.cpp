#include "PlayerView2D.h"
#include <QPainter>
#include "playerobject.h"

PlayerView2D::PlayerView2D(QGraphicsItem *parent) : QGraphicsItem(parent)  {}

void PlayerView2D::draw(std::shared_ptr<const GameObject> go) {

    auto playerObject = std::dynamic_pointer_cast<const PlayerObject>(go);
    if (!playerObject) return;

    float x = playerObject->getProtagonist().getXPos()*50;
    float y = playerObject->getProtagonist().getYPos()*50;
    qDebug() << "Updating PlayerView2D to X:" << x << ", Y:" << y;
    setPos(x+25,y+25);

    // Trigger a repaint
    QGraphicsItem::update();
}

QRectF PlayerView2D::boundingRect() const {
    qDebug() << "BoundingRect called. playerX:" << playerX << ", playerY:" << playerY;
    return QRectF(-10, -10, 20, 20); // Adjust based on shape size
}

void PlayerView2D::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/) {
    qDebug() << "Paint called. playerX:" << playerX << ", playerY:" << playerY;
    painter->setBrush(Qt::blue); // Set arbitrary shape color
    painter->setPen(Qt::NoPen);  // No border
    painter->drawEllipse(-10,-10, 20, 20); // Circle with radius 10
}
