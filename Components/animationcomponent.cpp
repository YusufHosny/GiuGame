#include "animationcomponent.h"

AnimationComponent::AnimationComponent() : once(false) {}

void AnimationComponent::setUpdateTime(qint64 ut)
{
    this->updateTime = ut;
}

// This should be called before the animation component is used, otherwise undefined
void AnimationComponent::setAnimation(unsigned int anim, unsigned int frameCnt)
{
    this->currentAnimation = anim;
    this->frameCnt = frameCnt;
    this->frameId = 0;
    this->updateTimeLeft = this->updateTime;
}

const unsigned int AnimationComponent::getAnimation() const
{
    return this->currentAnimation;
}

const unsigned int AnimationComponent::getFrame() const
{
    return this->frameId;
}

void AnimationComponent::setOnce(bool once)
{
    this->once = once;
}


void AnimationComponent::step_component(GameObject& owner, qint64 deltaT)
{
    if(this->updateTimeLeft > 0) {
        this->updateTimeLeft -= deltaT;
    }
    else {
        this->frameId++;
        this->updateTimeLeft = this->updateTime;
        // stop if one shot animation, otherwise reset
        if(this->frameId == this->frameCnt-1) {
            if(this->once) {
                this->setActive(false);
            }
            else {
                this->frameId = 0;
            }
        }
    }
}
