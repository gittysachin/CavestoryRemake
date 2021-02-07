//
// Created by blockost on 2/4/19.
//

#ifndef CAVESTORY_TILE_H
#define CAVESTORY_TILE_H


#include <ostream>
#include <vector>
#include <util/Globals.h>
#include "Tileset.h"
#include "Graphics.h"

class Tile {

public:

    /**
     * Constructor.
     *
     * Tile's id is expected to be the "true" position of the tile in the tileset, without the
     * offset by Tileset's firstgid.
     */
    Tile(unsigned id, unsigned positionInJson, const Tileset &tileset);

    /**
     * Destructor.
     */
    virtual ~Tile();

    /**
     * Computes and sets the original position of the tile in the tileset (in pixels).
     */
    void setPositionInTileset();

    /**
     * Computes and sets where the tile should be draw on the map (i.g on the screen).
     */
    void setDestinationOnMap(unsigned mapWidth);

    /**
     * Draws the tile on the screen.
     */
    virtual void draw(Graphics &graphics) const;

    /**
     * Updates the tile based on elapsed time since last update.
     *
     * XXX 09-Mar-2019 blockost This method is a no-op for class Tile but is defined here so
     * that we can use polymorphism and dynamic binding on Tile/AnimatedTile classes
     */
    virtual void update(unsigned elapsedTime);

    /**
     * Defines stream output operator.
     */
    friend std::ostream &operator<<(std::ostream &os, const Tile &tile);

protected:
    unsigned id;
    unsigned positionInJson;
    Tileset tileset;
    Coord sourceInTileset;
    Coord destinationOnMap;
};


#endif //CAVESTORY_TILE_H
