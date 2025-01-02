#include "animationcomponent.h"

AnimationComponent::AnimationComponent() {}

void AnimationComponent::setUpdateTime(qint64 ut)
{
    this->updateTime = ut;
}

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

void AnimationComponent::step_component(GameObject& owner, qint64 deltaT)
{
    if(this->updateTimeLeft > 0) {
        this->updateTimeLeft -= deltaT;
    }
    else {
        this->frameId = (this->frameId + 1) % this->frameCnt;
        this->updateTimeLeft = this->updateTime;
    }
}
