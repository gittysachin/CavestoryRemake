
#include "Game.h"

/**
 * Application's entry point.
 */
int main() {
    std::cout << "Initializing SDL subsystems..." << std::endl;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    Game game;
    return 0;
}