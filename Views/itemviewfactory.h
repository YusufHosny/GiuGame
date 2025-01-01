#ifndef ITEMVIEWFACTORY_H
#define ITEMVIEWFACTORY_H

#include "giugameconfig.h"
#include "itemview.h"

class ItemViewFactory
{
private:
    ViewType type;

public:
    ItemViewFactory(ViewType t);

    ItemView* makeTile(int x, int y, float luminance);
    ItemView* makePlayer();
    ItemView* makeEnemy();
    ItemView* makePEnemy();
    ItemView* makeBEnemy();
    ItemView* makeHealthPack();
};

#endif // ITEMVIEWFACTORY_H
