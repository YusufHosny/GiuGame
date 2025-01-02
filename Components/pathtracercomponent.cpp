#include "pathtracercomponent.h"
#include "pathobject.h"

PathTracerComponent::PathTracerComponent() {}

void PathTracerComponent::setCurrent(const Tile& tile) {
    this->xprev = tile.getXPos();
    this->yprev = tile.getYPos();
}

void PathTracerComponent::reset(TileObject& owner) {
    for(auto& path : owner.findChildren<PathObject>()) {
        owner.removeChild(path);
    }
}

void PathTracerComponent::step_component(GameObject &owner, qint64 deltaT)
{
    TileObject& t = dynamic_cast<TileObject&>(owner); // throws if non-tileobject owns this component

    // remove dead paths
    for(auto& path : owner.findChildren<PathObject>()) {
        if(path->getTile().getValue() < 0) owner.removeChild(path);
    }

    // on position change
    if(t.getTile().getXPos() != this->xprev || t.getTile().getYPos() != this->yprev) {

        // draw path object
        std::shared_ptr<PathObject> po = std::shared_ptr<PathObject>( new PathObject(this->xprev, this->yprev) );
        po->init();
        t.addChild(po);

        // update position buffer
        this->setCurrent(t.getTile());
    }

}
