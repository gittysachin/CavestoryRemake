//
// Created by blockost on 2/2/19.
//

#ifndef CAVESTORY_LEVEL_H
#define CAVESTORY_LEVEL_H


#include <util/Globals.h>
#include <vector>
#include <ostream>
#include "../lib/nlohmann/json.hpp"

#include "Graphics.h"
#include "tile/Tile.h"
#include "tile/Tileset.h"
#include "BoundingBox.h"
#include "Slope.h"

using json = nlohmann::json;

class Level {
public:

    /**
     * Constructor.
     *
     * This constructor is used when calling std::make_unique<Level>()
     */
    Level(Graphics &graphics, const std::string &mapName);

    /**
     * Destructor.
     */
    ~Level();

    /**
     * Retrieves all the bounding boxes of the current level.
     */
    const std::vector<BoundingBox> &getBoundingBoxes();

    /**
     * Retrieves player's spawn point.
     */
    const Coord &getPlayerSpawnPoint() const;

    /**
     * Sets player's spawn point to the given x and y.
     */
    void setPlayerSpawnPoint(int x, int y);

    /**
     * Draws the level on the screen.
     */
    void draw(Graphics &graphics);

    /**
     * Update level based on elapsed time since last update.
     */
    void update(unsigned elapsedTime);


private:
    SDL_Texture *mapTexture;
    Coord mapSize = Coord(0, 0);
    std::string mapName;

    // Map of all the spawn points for the current level
    std::map<std::string, Coord> spawnPoints;

    // List of tilesets for the current level
    std::vector<Tileset> tilesets;

    // List of tiles for the current level
    std::vector<std::unique_ptr<Tile>> tiles;

    // List of collisions blocks for the current level
    std::vector<BoundingBox> boundingBoxes;

    // List of slopes for the current level
    std::vector<Slope> slopes;

    // Load map from JSON file into objects
    void loadMap(Graphics &graphics);

    // Parse collision objects in the map
    void parseCollisionObjects(const json &collisionObjects);

    // Parse spawn point object in the map
    void parseSpawnPointObjects(const json &spawnPointObjects);

    // Parse slope object in the map
    void parseSlopeObjects(const json &slopeObjects);

    // Retrieves the tileset where the given tile comes from
    const Tileset getTilesetAssociatedToTileId(unsigned gid) const;
};

#endif //CAVESTORY_LEVEL_H
