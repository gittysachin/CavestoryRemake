//
// Created by blockost on 1/28/19.
//

#ifndef CAVESTORY_PLAYER_H
#define CAVESTORY_PLAYER_H

#include <string>
#include <bits/unique_ptr.h>
#include <cmath>
#include "sprite/AnimatedSprite.h"
#include "util/Globals.h"
#include "BoundingBox.h"

class Player {
public:

    /**
     * Constructor.
     *
     * This constructor is used when calling std::make_unique<Player>()
     */
    Player(Graphics &graphics, Coord spawnPoint);

    /**
     * Destructor.
     */
    ~Player();

    /**
     * Sets the given animation as the one to be played.
     */
    void setAnimation(const std::string &animationName);

    /**
     * Moves the player by updating its position (taking into account screen size).
     */
    void move(float elapsedTime);

    /**
     * Handles SDL Event related to the player.
     */
    void handleEvent(const SDL_Event &event);

    /**
     * Handles player's collisions with the world.
     *
     */
    void handleCollisions(const std::vector<BoundingBox> &boundingBoxes);

    /**
     * Draws the player to the screen (delegating logic to the sprite).
     */
    void draw(Graphics &graphics) const;

    /**
     * Updates player based on elapsed time since last update.
     */
    void update(unsigned int elapsedTime);

private:

    // Nominal player acceleration along the X-axis (lateral movement)
    constexpr static float PLAYER_NOMINAL_ACC_X = 0.002f;
    // Nominal player acceleration along the Y-axis
    constexpr static float PLAYER_NOMINAL_ACC_Y = 0.005f;
    // Maximum player speed along the X-axis
    constexpr static float PLAYER_MAX_VEL_X = 0.35f;
    // Maximum player speed along the Y-axis
    constexpr static float PLAYER_MAX_VEL_Y = 0.25f;
    // Player's jump velocity
    constexpr static float JUMP_VELOCITY = -0.35f;
    // The value player's velocity will be reduced to if the jump key is released
    constexpr static float JUMP_CUT_VELOCITY = -0.07f;

    std::unique_ptr<AnimatedSprite> sprite;
    float posX, posY;
    float velX, velY;
    float accX, accY;
    // The direction the player is currently facing to
    Direction facingDirection;
    // Is the player on the ground?
    bool isOnTheGround;

    /**
     * Utility method to move the player to the left;
     */
    void moveLeft();

    /**
     * Utility method to move the player to the right.
     */
    void moveRight();

    /**
     * Utility method to stop the player from moving.
     */
    void stopMoving();

    /**
     * Utility method to make the player jump. Jumping does not change facing direction.
     */
    void jump();

    /**
     * Utility method to stop the player from moving upwards and cut its velocity to a lower value
     * (allowing the player to start falling).
     */
    void cutJumping();

    /**
     * Utility method that applies gravity to the player.
     */
    void applyGravity(unsigned elapsedTime);

    /**
     * Utility method to gradually reduce lateral movement (i.e movement along the x-axis) to 0 so
     * that the player stops moving smoothly.
     */
    void applyFriction(unsigned elapsedTime);
};


#endif //CAVESTORY_PLAYER_H
