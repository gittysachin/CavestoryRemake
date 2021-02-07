//
// Created by blockost on 2/4/19.
//

#include <exceptions/InvalidLevelException.h>
#include "Tileset.h"

Tileset::Tileset(const std::string &texturePath, unsigned int firstTileId, unsigned int width,
                 unsigned int height, const std::vector<TileAnimation> &animations)
        : texturePath(texturePath), firstTileId(firstTileId), width(width), height(height),
          animations(animations) {}

Tileset::~Tileset() = default;

const std::string &Tileset::getTexturePath() const {
    return this->texturePath;
}

unsigned Tileset::getFirstTileId() const {
    return this->firstTileId;
}

unsigned Tileset::getWidth() const {
    return width;
}

unsigned Tileset::getHeight() const {
    return height;
}

bool Tileset::hasAnimationForTile(unsigned tileId) const {
    for (const auto &animation : this->animations) {
        if (animation.getFirstTileOfAnimation() == tileId) {
            return true;
        }
    }

    return false;
}

const TileAnimation &Tileset::getAnimationForTile(unsigned tileId) const {
    for (const auto &animation : this->animations) {
        if (animation.getFirstTileOfAnimation() == tileId) {
            return animation;
        }
    }

    std::stringstream ss;
    ss << "tileId: " << tileId << " should no be animated because it has no animation defined";
    throw InvalidLevelException(ss);
}

std::ostream &operator<<(std::ostream &ostream, const Tileset &tileset) {
    ostream << "texturePath: " << tileset.texturePath << " firstTileId: " << tileset.firstTileId
            << " width: " << tileset.width << " height: " << tileset.height;
    return ostream;
}
