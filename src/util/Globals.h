//
// Created by blockost on 1/28/19.
//

#ifndef CAVESTORY_GLOBALS_H
#define CAVESTORY_GLOBALS_H

#include <ostream>

namespace Globals {

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    // In cavestory, sprites are 16x16 pixels
    const int SPRITE_WIDTH = 16;
    const int SPRITE_HEIGHT = 16;

    // In cavestory, backgrounds are 64x64 pixels
    const int BG_WIDTH = 64;
    const int BG_HEIGHT = 64;

    // In order to look nice, sprites should be scale by 2 (16x16 is too little)
    const int SPRITE_SCALE = 2;

    namespace World {
        // Gravity force (contant pull towards the bottom of the screen) to apply to objects
        const float GRAVITY = 0.0005f;
        // Maximum gravity force that can be applied
        const float GRAVITY_CAP = 0.20f;
        // Friction to be applied to counter objects movement
        const float FRICTION = 0.01f;
    }
}

enum class Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Coord {
    int x, y;

    Coord() : x(0), y(0) {};

    Coord(int x, int y) : x(x), y(y) {};

    friend Coord operator*(const Coord &coord, int factor) {
        return {coord.x * factor, coord.y * factor};
    }

    friend std::ostream &operator<<(std::ostream &ostream, const Coord &coord) {
        ostream << "(" << coord.x << "," << coord.y << ")";
        return ostream;
    }
};

struct RgbColor {
    int red, green, blue;

    RgbColor() : red(0), green(0), blue(0) {}

    RgbColor(int red, int green, int blue) : red(red), green(green), blue(blue) {}
};

enum class Side {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    NONE
};

#endif //CAVESTORY_GLOBALS_H
