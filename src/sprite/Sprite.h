//
// Created by blockost on 2/16/19.
//

#ifndef CAVESTORY_SPRITE_H
#define CAVESTORY_SPRITE_H


#include <BoundingBox.h>

class Sprite {
public:

    /**
     * Constructor.
     */
    explicit Sprite(SDL_Texture *texture);

    /**
     * Pure virtual destructor.
     *
     * The trick here is to declare the destructor as pure virtual so that the class becomes
     * abstract without the need to define other pure virtual methods. However, a default
     * implementation is supplied because destructors must have one in order to instantiate derived
     * classes.
     */
    virtual ~Sprite() = 0;

    /**
     * Retrieves sprite's bounding box.
     */
    const BoundingBox &getBoundingBox() const;

    /**
     * Moves the sprite's bounding box to the given x and y.
     */
    void moveBoundingBox(int x, int y);

    /**
     * Draws the given rectangle at the given x and y.
     */
    void draw(Graphics &graphics, SDL_Rect &sourceRect, int y, int x) const;

private:
    // The texture from which the sprite comes from
    SDL_Texture *texture{};

    // The bounding box around the sprite (for collisions detection)
    BoundingBox boundingBox;
};


#endif //CAVESTORY_SPRITE_H
