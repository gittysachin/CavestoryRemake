//
// Created by blockost on 1/24/19.
//

#ifndef CAVESTORY_GRAPHICS_H
#define CAVESTORY_GRAPHICS_H


#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

#include "util/Flags.h"
#include "util/Globals.h"

class Graphics {

public:
    /**
     * Default constructor
     */
    Graphics();

    /**
     * Destructor.
     */
    ~Graphics();

    /**
     * Creates an SDL window and an SDL renderer. This method should be called before anything else.
     */
    void createWindowAndRenderer();

    /**
    * Loads a texture from disk and cache it for future us.
    * If texture has already been loaded, does nothing.
    */
    void loadTexture(const std::string &filePath);

    /**
     * Retrieves a texture previously loaded.
     */
    SDL_Texture *getTexture(const std::string &filePath);

    /**
     * Copy the texture into the renderer.
     * All the textures inside the renderer will be drawn to the screen by calling the render() method
     */
    void copyTextureToRenderer(SDL_Texture *texture, const SDL_Rect *sourceRect,
                               const SDL_Rect *destRect);

    /**
     * Draws the line between the two given end points to the rendering target.
     */
    void drawLineToRenderer(Coord p1, Coord p2);

    /**
     * Draws the given rectangle with the given color to the rendering target.
     */
    void drawRectToRenderer(const SDL_Rect *rect);

    /**
     * Draws everything stored in the renderer on the actual window.
     */
    void render();

    /**
     * Clears the rendering target with the current draw color (set by SDL_SetRenderDrawColor).
     * The render() method still needs to be called for the screen to be updated.
     */
    void clear();

private:
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    std::map<std::string, SDL_Texture *> textures;
};


#endif //CAVESTORY_GRAPHICS_H
