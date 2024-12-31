#include "autoplaycomponent.h"
#include "playerobject.h"

AutoPlayComponent::AutoPlayComponent() : active(false) {}

void AutoPlayComponent::toggleAutoplay() {
    this->active = !this->active;
}

void AutoPlayComponent::step_component(GameObject& owner) {
    if(!this->active) return;

    PlayerObject& player = dynamic_cast<PlayerObject&>(owner); // throws if non-player owns this component
    player.move(Direction::RIGHT);
}
