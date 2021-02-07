//
// Created by blockost on 3/9/19.
//

#ifndef CAVESTORY_ANIMATEDTILE_H
#define CAVESTORY_ANIMATEDTILE_H

#include "Tile.h"

/**
 * This class holds the logic to animate a Tile.
 *
 * Basically, this class cycle-though a list of tile that represents an animation and update its
 * tileId if the current Tile has reached its max lifetime (it supports different durations for
 * each Tile).
 */
class AnimatedTile : public Tile {

public:
    /**
     * Contructor.
     */
    AnimatedTile(unsigned tileId, unsigned positionInJson, const Tileset &tileset,
                 TileAnimation tileAnimation);

    /**
     * Destructor.
     */
    ~AnimatedTile() override;

    /**
     * Updates the tile based on elapsed time since last update.
     */
    void update(unsigned elaspedTime) override;

private:
    unsigned elapsedTime;
    TileAnimation animation;
};


#endif //CAVESTORY_ANIMATEDTILE_H
