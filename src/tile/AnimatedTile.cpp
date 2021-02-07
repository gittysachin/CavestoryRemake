//
// Created by blockost on 3/9/19.
//

#include "AnimatedTile.h"

AnimatedTile::AnimatedTile(unsigned tileId, unsigned positionInJson, const Tileset &tileset,
                           TileAnimation tileAnimation)
        : Tile(tileId, positionInJson, tileset), elapsedTime(0), animation(tileAnimation) {

}

AnimatedTile::~AnimatedTile() = default;

void AnimatedTile::update(unsigned elaspedTime) {
    this->elapsedTime += elaspedTime;

    if (this->elapsedTime >= this->animation.getMaxLifetimeOfTile()) {
        this->id = this->animation.getNextTileOfAnimation();
        this->setPositionInTileset();

        // Reset elapsedTime because the tile has been updated
        this->elapsedTime = 0;
    }
}
