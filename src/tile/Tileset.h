//
// Created by blockost on 2/4/19.
//

#ifndef CAVESTORY_TILESET_H
#define CAVESTORY_TILESET_H


#include <string>
#include <iostream>
#include <vector>
#include "TileAnimation.h"

class Tileset {
public:

    /**
     * Constructor.
     */
    Tileset(const std::string &texturePath, unsigned firstTileId, unsigned width, unsigned height,
            const std::vector<TileAnimation> &animations);

    /**
     * Destructor.
     */
    ~Tileset();

    const std::string &getTexturePath() const;

    unsigned getFirstTileId() const;

    unsigned getWidth() const;

    unsigned getHeight() const;

    /**
     * Determines whether the given tile needs to be animated (only the first tile in an animation
     * needs to be animated).
     */
    bool hasAnimationForTile(unsigned tileId) const;

    /**
     * Retrieves animation info for the given tile.
     */
    const TileAnimation &getAnimationForTile(unsigned tileId) const;

    /**
     * Defined stream output operator.
     */
    friend std::ostream &operator<<(std::ostream &ostream, const Tileset &tileset);


private:
    std::string texturePath;
    unsigned firstTileId;
    unsigned width;
    unsigned height;

    // List of animations (list of pair of tile id and duration) for this tileset.
    std::vector<TileAnimation> animations;
};


#endif //CAVESTORY_TILESET_H
