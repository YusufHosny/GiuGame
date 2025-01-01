#include "itemview.h"
#include "giugameconfig.h"

QRectF ItemView::boundingRect() const {
    int tileSideLen = GiuGameConfig::getInstance().config2d.tileSideLen;
    return QRectF(-tileSideLen/2, -tileSideLen/2, tileSideLen, tileSideLen);
};
