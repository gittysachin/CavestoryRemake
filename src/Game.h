//
// Created by blockost on 1/27/19.
//

#ifndef CAVESTORY_GAME_H
#define CAVESTORY_GAME_H


#include "Graphics.h"
#include "Player.h"
#include "Level.h"

/**
 * This class contains the logic of the main game loop.
 */
class Game {
public:
    /**
     * Default constructor.
     */
    Game();

    /**
     * Destructor.
     */
    ~Game();

private:
    // TODO 02-Feb-2019 blockost Limit frame per second?
    // Max number of frame per second
    const int FPS = 50;
    std::unique_ptr<Graphics> graphics;
    std::unique_ptr<Player> player;
    std::unique_ptr<Level> level;

    /**
     * Starts the game loop.
     */
    void startGameLoop();

    /**
     * This method draws everything the game needs to make appear on the screen and will be called
     * at then end of each game loop.
     */
    void draw();

    /**
     * Mother-method to update all game components based on time elapsed since last update.
     */
    void update(unsigned elapsedTime);
};


#endif //CAVESTORY_GAME_H
