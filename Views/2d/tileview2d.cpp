#include "tileview2d.h"
#include "giugameconfig.h"
#include <QPainter>

TileView2d::TileView2d(int x, int y, float luminance, QGraphicsItem *parent) : ItemView(parent), luminance(luminance)  {
    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;

    this->x = x * tileSideLen;
    this->y = y * tileSideLen;

}

void TileView2d::draw(std::shared_ptr<const GameObject> go) {

    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
    this->setPos(x+tileSideLen/2,y+tileSideLen/2);

    QGraphicsItem::update();
}


void TileView2d::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    float lum255 = this->luminance*255;
    QColor c(lum255, lum255, lum255);
    painter->setBrush(c);
    painter->setPen(Qt::NoPen);
    painter->drawRect(this->boundingRect());
}
