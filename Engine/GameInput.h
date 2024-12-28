#ifndef GAMEINPUT_H
#define GAMEINPUT_H

#include <functional>

enum class GameInputType {
    PLAYERUP,
    PLAYERDOWN,
    PLAYERLEFT,
    PLAYERRIGHT,

    SWITCHVIEWTEXT,
    SWITCHVIEW2D,
    SWITCHVIEW3D,

    ZOOMIN,
    ZOOMOUT,

    GOTO
};


class GameInput {

public:
    GameInput() = delete;
    GameInput(GameInputType type, int parameter = 0): type(type), parameter(parameter) {};

    const GameInputType type;
    const int parameter;

    bool operator<(const GameInput other) const {
        return std::less<GameInputType>()(type, other.type);
    }

};



#endif // GAMEINPUT_H
