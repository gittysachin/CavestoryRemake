//
// Created by blockost on 2/24/19.
//

#include "Slope.h"

Slope::Slope(const Coord p1, const Coord p2) : isVisible(true),
                                               points(p1 * Globals::SPRITE_SCALE,
                                                      p2 * Globals::SPRITE_SCALE) {}

Slope::~Slope() = default;

void Slope::draw(Graphics &graphics) const {
    if (isVisible) {
        graphics.drawLineToRenderer(this->points.first, this->points.second);
    }
}
