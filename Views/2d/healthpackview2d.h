#ifndef HEALTHPACKVIEW2D_H
#define HEALTHPACKVIEW2D_H

#include "animateditemview.h"

class HealthPackView2d : public AnimatedItemView {
public:

    HealthPackView2d(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

private:

    static std::map<unsigned int,  std::vector<QPixmap>> sprites;

    std::map<unsigned int,  std::vector<QPixmap>>& getSprites() override;
    void loadSprites() override;

};

#endif // HEALTHPACKVIEW2D_H
