#ifndef DOORVIEW2D_H
#define DOORVIEW2D_H

#include "animateditemview.h"

class DoorView2d : public AnimatedItemView {
public:

    DoorView2d(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

private:

    static std::map<unsigned int,  std::vector<QPixmap>> sprites;

    std::map<unsigned int,  std::vector<QPixmap>>& getSprites() override;
    void loadSprites() override;

};

#endif // DOORVIEW2D_H
