//
// Created by blockost on 3/9/19.
//

#include "TileAnimation.h"

TileAnimation::TileAnimation(const std::vector<std::pair<unsigned int, unsigned int>> &animations)
        : animations(animations), currentAnimationIndex(0) {}

TileAnimation::~TileAnimation() = default;

unsigned TileAnimation::getFirstTileOfAnimation() const {
    if (this->animations.empty()) {
        return 0;
    }

    return this->animations.at(0).first;
}

unsigned TileAnimation::getNextTileOfAnimation() {
    if (this->currentAnimationIndex == this->animations.size() - 1) {
        this->currentAnimationIndex = 0;
    } else {
        this->currentAnimationIndex++;
    }

    return this->animations[this->currentAnimationIndex].first;
}

unsigned TileAnimation::getMaxLifetimeOfTile() const {
    return this->animations.at(this->currentAnimationIndex).second;
}
