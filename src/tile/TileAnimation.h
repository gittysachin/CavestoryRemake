//
// Created by blockost on 3/9/19.
//

#ifndef CAVESTORY_TILEANIMATION_H
#define CAVESTORY_TILEANIMATION_H


#include <vector>

/**
 * Helper class that gathers information on tiles animations.
 */
class TileAnimation {

public:

    /**
     * Constructor.
     */
    explicit TileAnimation(const std::vector<std::pair<unsigned int, unsigned int>> &animations);

    /**
     * Destructor.
     */
    ~TileAnimation();

    /**
     * Retrieves the first tileId of the animation.
     */
    unsigned getFirstTileOfAnimation() const;

    unsigned getNextTileOfAnimation();

    unsigned getMaxLifetimeOfTile() const;

private:
    std::vector<std::pair<unsigned, unsigned>> animations;
    unsigned currentAnimationIndex = 0;

};


#endif //CAVESTORY_TILEANIMATION_H
