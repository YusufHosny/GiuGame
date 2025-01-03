#ifndef PLAYERVIEW2D_H
#define PLAYERVIEW2D_H

#include "animateditemview.h"

class PlayerView2d : public AnimatedItemView {

public:

    PlayerView2d(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

private:

    static std::map<unsigned int,  std::vector<QPixmap>> sprites;

    std::map<unsigned int,  std::vector<QPixmap>>& getSprites() override;
    void loadSprites() override;

};

#endif // PLAYERVIEW2D_H
