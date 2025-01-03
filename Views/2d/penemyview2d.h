#ifndef PENEMYVIEW2D_H
#define PENEMYVIEW2D_H

#include "animateditemview.h"

class PEnemyView2d: public AnimatedItemView
{
public:
    PEnemyView2d(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

private:

    static std::map<unsigned int,  std::vector<QPixmap>> sprites;

    std::map<unsigned int,  std::vector<QPixmap>>& getSprites() override;
    void loadSprites() override;

};

#endif // PENEMYVIEW2D_H
