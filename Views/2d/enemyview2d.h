#ifndef ENEMYVIEW2D_H
#define ENEMYVIEW2D_H

#include "animateditemview.h"

class EnemyView2d: public AnimatedItemView
{

public:
    EnemyView2d(QGraphicsItem *parent = nullptr);
    void draw(std::shared_ptr<const GameObject> go) override;

private:
    static std::map<unsigned int,  std::vector<QPixmap>> sprites;

    std::map<unsigned int,  std::vector<QPixmap>>& getSprites() override;
    void loadSprites() override;


};

#endif // ENEMYVIEW2D_H
