//
// Created by blockost on 2/12/19.
//

#ifndef CAVESTORY_BOUNDINGBOX_H
#define CAVESTORY_BOUNDINGBOX_H


#include <ostream>
#include "Graphics.h"

/**
 * A bounding box is a virtual rectangle that encapsultes a game element in order to detect
 * collisions with it. Top-left corner is located at (x, y) and bottom-right corner is located at
 * (x + width, y + height)
 */
class BoundingBox {
public:

    /**
     * Constructor.
     */
    BoundingBox(int x, int y, int width, int height);

    /**
     * Destructor.
     */
    ~BoundingBox();

    /**
     * Utility method to set all 4 coords of the bounding box.
     */
    void set(int x, int y);

    /**
     * Retrieves bounding box's width.
     */
    int getWidth() const;

    /**
     * Retrieve bounding box's height.
     */
    int getHeight() const;

    /**
     * Retrieves where the left edge of the bouding box is starting.
     */
    int getLeftEdge() const;

    /**
     * Retrieved where the right edge of the boudning box is starting.
     */
    int getRightEdge() const;

    /**
     * Retrieves where the top edge of the bounding box is starting.
     */
    int getTopEdge() const;

    /**
     * Retrieves where the bottom edge of the bounding box is starting.
     */
    int getBottomEdge() const;

    /**
     * Determines which side the current bounding box is colliding with.
     */
    Side getCollidingSide(const BoundingBox &other) const;

    /**
     * Draws the bounding box to the screen.
     */
    void draw(Graphics &graphics) const;

    friend std::ostream &operator<<(std::ostream &os, const BoundingBox &box);

private:
    int x, y, width, height;
    bool isVisible;

    /**
     * Determines if current bounding box is colliding with another.
     */
    bool isCollidingWith(const BoundingBox &other) const;
};


#endif //CAVESTORY_BOUNDINGBOX_H
