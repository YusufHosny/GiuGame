#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <gameobjectcomponent.h>
#include <QIntegerForSize>

class AnimationComponent : public GameObjectComponent
{
public:
    AnimationComponent();

    void setUpdateTime(qint64 ut);

    void setAnimation(unsigned int anim, unsigned int frameCnt);

    const unsigned int getAnimation() const;
    const unsigned int getFrame() const;

    void setOnce(bool once);

    void step_component(GameObject& owner, qint64 deltaT = 0) override;

private:
    unsigned int currentAnimation; // weakly typed enum container type
    unsigned int frameCnt; // number of available frames for current animations
    unsigned int frameId; // int deciding which frame to use

    bool once;

    qint64 updateTime; // time in msec per each frame of the animation
    qint64 updateTimeLeft;

};

#endif // ANIMATIONCOMPONENT_H
