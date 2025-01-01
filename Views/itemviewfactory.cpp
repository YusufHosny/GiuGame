#include "itemviewfactory.h"

#include "penemyview2d.h"
#include "benemyview2d.h"
#include "enemyview2d.h"
#include "playerview2d.h"
#include "healthpackview2d.h"
#include "tileview2d.h"

#include "tileviewtext.h"
#include "penemyviewtext.h"
#include "benemyviewtext.h"
#include "enemyviewtext.h"
#include "playerviewtext.h"
#include "healthpackviewtext.h"

ItemViewFactory::ItemViewFactory(ViewType t) : type(t) {}

ItemView* ItemViewFactory::makeTile(int x, int y, float luminance) {
    ItemView* out;
    if(type == ViewType::VIEW2D) {
        out = new TileView2d(x, y, luminance);
    }
    else if(type == ViewType::VIEWTEXT) {
        out = new TileViewText(x, y, luminance);
    }
    return out;
}


ItemView* ItemViewFactory::makePlayer() {
    ItemView* out;
    if(type == ViewType::VIEW2D) {
        out = new PlayerView2D();
    }
    else if(type == ViewType::VIEWTEXT) {
        out = new PlayerViewText();
    }
    return out;
}

ItemView* ItemViewFactory::makeEnemy() {
    ItemView* out;
    if(type == ViewType::VIEW2D) {
        out = new EnemyView2D();
    }
    else if(type == ViewType::VIEWTEXT) {
        out = new EnemyViewText();
    }
    return out;
}

ItemView* ItemViewFactory::makePEnemy() {
    ItemView* out;
    if(type == ViewType::VIEW2D) {
        out = new PEnemyView2D();
    }
    else if(type == ViewType::VIEWTEXT) {
        out = new PEnemyViewText();
    }
    return out;
}

ItemView* ItemViewFactory::makeBEnemy() {
    ItemView* out;
    if(type == ViewType::VIEW2D) {
        out = new BEnemyView2D();
    }
    else if(type == ViewType::VIEWTEXT) {
        out = new BEnemyViewText();
    }
    return out;
}

ItemView* ItemViewFactory::makeHealthPack() {
    ItemView* out;
    if(type == ViewType::VIEW2D) {
        out = new HealthPackView2D();
    }
    else if(type == ViewType::VIEWTEXT) {
        out = new HealthPackViewText();
    }
    return out;
}