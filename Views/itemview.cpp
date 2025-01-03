#include "itemview.h"
#include "giugameconfig.h"

ItemView::ItemView(QGraphicsItem *parent): QGraphicsItem(parent) {};


QRectF ItemView::boundingRect() const {
    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
    return QRectF(-tileSideLen/2, -tileSideLen/2, tileSideLen, tileSideLen);
};
