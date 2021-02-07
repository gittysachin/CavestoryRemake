//
// Created by blockost on 1/27/19.
//

#ifndef CAVESTORY_ANIMATEDSPRITE_H
#define CAVESTORY_ANIMATEDSPRITE_H


#include <SDL2/SDL_rect.h>
#include <vector>
#include <string>
#include "Graphics.h"
#include "BoundingBox.h"
#include "Sprite.h"

class AnimatedSprite : public Sprite {
public:

    /**
     * Constructor.
     *
     * This constructor is used when calling std::make_unique<AnimatedSprite>()
     */
    AnimatedSprite(SDL_Texture *texture, float maxFrameLifetime);

    /**
     * Destructor.
     */
    ~AnimatedSprite() override;

    /**
     * Adds a animation to the list of this sprite's animation.
     */
    void addAnimations(const std::string &animationName, int numberOfFrames, int x, int y);

    /**
     * Resets the list of animations for this sprite.
     */
    void resetAnimations();

    /**
     * Sets the given animation as the one to be played.
     */
    void setAnimation(const std::string &animationName);

    /**
     * Draws (copies) the current frame of the sprite to the renderer at position x and y.
     */
    void draw(Graphics &graphics, int x, int y) const;

    /**
     * Updates the sprite animation based on the elapsed time since last update. Basically, it
     * updates the index of the frame that will be drawn afterwards.
     */
    void update(int elapsedTime);

private:
    // Index of the current frame in the current animation
    unsigned int frameIndex = 0;
    // Max number of milliseconds to wait before changing the frame
    float maxFrameLifetime = 0;
    // Number of milliseconds since the last frame update
    float elapsedTime = 0;
    // String identifier for the current animation being played
    std::string currentAnimation;
    // List of all animations
    std::map<std::string, std::vector<SDL_Rect>> animations{};
};


#endif //CAVESTORY_ANIMATEDSPRITE_H
