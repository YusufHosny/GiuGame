#ifndef BENEMYVIEW2D_H
#define BENEMYVIEW2D_H

#include "animateditemview.h"

class BEnemyView2d: public AnimatedItemView
{

public:

    BEnemyView2d(QGraphicsItem *parent = nullptr);

    void draw(std::shared_ptr<const GameObject> go) override;

private:
    static std::map<unsigned int,  std::vector<QPixmap>> sprites;

    std::map<unsigned int,  std::vector<QPixmap>>& getSprites() override;
    void loadSprites() override;


};

#endif // BENEMYVIEW2D_H
