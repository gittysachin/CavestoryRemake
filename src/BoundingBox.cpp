//
// Created by blockost on 2/12/19.
//

#include <iostream>
#include <util/Globals.h>
#include <algorithm>
#include "BoundingBox.h"

BoundingBox::BoundingBox(int x, int y, int width, int height) : x(x * Globals::SPRITE_SCALE),
                                                                y(y * Globals::SPRITE_SCALE),
                                                                width(width *
                                                                      Globals::SPRITE_SCALE),
                                                                height(height *
                                                                       Globals::SPRITE_SCALE),
                                                                isVisible(true) {}

BoundingBox::~BoundingBox() = default;

void BoundingBox::set(int x, int y) {
    this->x = x;
    this->y = y;
}

int BoundingBox::getWidth() const {
    return this->width;
}

int BoundingBox::getHeight() const {
    return this->height;
}

int BoundingBox::getLeftEdge() const {
    return this->x;
}

int BoundingBox::getRightEdge() const {
    return this->x + width;
}

int BoundingBox::getTopEdge() const {
    return this->y;
}

int BoundingBox::getBottomEdge() const {
    return this->y + height;
}

Side BoundingBox::getCollidingSide(const BoundingBox &other) const {
    if (this->isCollidingWith(other)) {
        // XXX 16-Feb-2019 blockost To compute which side is colliding with the rectangle, we can
        // compute the "depth of intrusion" for each side of the rectangles to determine which side
        // is most involved in the collision (which one is the closest to the colliding rectangle)

        // XXX 16-Feb-2019 blockost This technique is working fine because rectangles are moving
        // slowing in the game but if there were too fast for the computation to determine the side
        // as soon at 2 rectangles collide then it would be faulty (e.g the rectangle went halfway
        // through the other and the computation takes place only at this moment)
        // If this is a case, we could store the previou position of the rectangle and base the
        // computation on these coordinates instead

        int amountLeftEdge = std::abs(this->getLeftEdge() - other.getRightEdge());
        int amountRightEdge = std::abs(this->getRightEdge() - other.getLeftEdge());
        int amountTopEdge = std::abs(this->getTopEdge() - other.getBottomEdge());
        int amountBottomEdge = std::abs(this->getBottomEdge() - other.getTopEdge());
        const std::vector<int> amounts{amountLeftEdge, amountRightEdge, amountTopEdge,
                                       amountBottomEdge};

        auto min = *std::min_element(amounts.begin(), amounts.end());

        if (min == amountLeftEdge)
            return Side::LEFT;
        if (min == amountRightEdge)
            return Side::RIGHT;
        if (min == amountTopEdge)
            return Side::TOP;

        return Side::BOTTOM;
    }

    return Side::NONE;
}

void BoundingBox::draw(Graphics &graphics) const {
    if (this->isVisible) {
        const SDL_Rect rect{this->x, this->y, this->width, this->height};
        graphics.drawRectToRenderer(&rect);
    }
}

std::ostream &operator<<(std::ostream &ostream, const BoundingBox &box) {
    ostream << "x: " << box.x << " y: " << box.y << " width: " << box.width << " height: "
            << box.height;
    return ostream;
}

bool BoundingBox::isCollidingWith(const BoundingBox &other) const {
    // XXX 12-Feb-2019 blockost Checking if the bounding box is totally outside of another is
    // simpler than checking if it's inside

    // If THIS left edge is on the right of OTHER right edge
    bool notColliding = this->getLeftEdge() > other.getRightEdge()
                        // if THIS right edge is on the left of OTHER left edge
                        || this->getRightEdge() < other.getLeftEdge()
                        // if THIS top edge is below other bottom edge
                        || this->getTopEdge() > other.getBottomEdge()
                        // if THIS bottom edge is above OTHER top edge
                        || this->getBottomEdge() < other.getTopEdge();

    return !notColliding;
}
