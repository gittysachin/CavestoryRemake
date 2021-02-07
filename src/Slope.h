//
// Created by blockost on 2/24/19.
//

#ifndef CAVESTORY_SLOPE_H
#define CAVESTORY_SLOPE_H


#include <util/Globals.h>
#include "Graphics.h"

/**
 * This class represents straight lines in the level that the player can collide with. It differs
 * from the Rectangle as it is a single straight line formed by two arbritray points in the map
 */
class Slope {
public:

    /**
     * Constructor.
     */
    Slope(Coord p1, Coord p2);

    /**
     * Destructor.
     */
    ~Slope();

    // TODO 03-Mar-2019 blockost implement a method to detect if a bounding box is
    //  colliding with a slope (since a slope will never be a moving object), i.e impl
    //  isCollidingWith(const Boundingbox& bbox)

    /**
     * Draws the slope onto the screen.
     */
    void draw(Graphics &graphics) const;

private:
    bool isVisible;
    std::pair<Coord, Coord> points;
};


#endif //CAVESTORY_SLOPE_H
