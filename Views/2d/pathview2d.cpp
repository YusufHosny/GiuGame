#include "pathview2d.h"
#include "giugameconfig.h"
#include "pathobject.h"
#include <QPainter>

PathView2d::PathView2d(QGraphicsItem* parent) : ItemView(parent)  {}

void PathView2d::draw(std::shared_ptr<const GameObject> go) {

    auto pathobj = std::dynamic_pointer_cast<const PathObject>(go);
    assert(pathobj);

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    float x = pathobj->getTile().getXPos()*tileSideLen;
    float y = pathobj->getTile().getYPos()*tileSideLen;
    this->setPos(x+tileSideLen/2,y+tileSideLen/2);

    this->opacity = static_cast<int>(pathobj->getTile().getValue() * 255);

    QGraphicsItem::update();
}

void PathView2d::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(QColor(200, 200, 10, this->opacity));
    painter->setPen(Qt::NoPen);
    painter->drawRect(this->boundingRect());
}
