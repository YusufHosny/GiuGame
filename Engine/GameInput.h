#ifndef GAMEINPUT_H
#define GAMEINPUT_H

#include <functional>

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

enum ViewType {
    VIEW2D, VIEW3D, VIEWTEXT
};


enum class GameInputType {
    PLAYERMOVE, // param: {0: up, 1: down, 2: left, 3: right}
    CAMERAMOVE, // param: {0: up, 1: down, 2: left, 3: right}
    SWITCHVIEW, // param: {0: 2d, 2: 3d, 3: text} might change tbh
    ZOOM, // param: {0: in, 1: out}
    GOTO, // param: id of target
    RESETCAMERA, // no param
    AUTOPLAY, // no param, toggles
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
