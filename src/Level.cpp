//
// Created by blockost on 2/2/19.
//

#include <sstream>
#include <fstream>
#include <tile/AnimatedTile.h>

#include "Level.h"
#include "exceptions/InvalidLevelException.h"

Level::Level(Graphics &graphics, const std::string &mapName) : mapSize(
        Coord(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT)), mapName(mapName) {

    // TODO 03-Mar-2019 blockost mapTexture is not used for the moment
    //this->mapTexture = graphics.getTexture("../data/backgrounds/bkBlue.png");
    this->loadMap(graphics);
}

Level::~Level() = default;

const std::vector<BoundingBox> &Level::getBoundingBoxes() {
    return this->boundingBoxes;
}

const Coord &Level::getPlayerSpawnPoint() const {
    return this->spawnPoints.at("PLAYER");
}

void Level::setPlayerSpawnPoint(int x, int y) {
    this->spawnPoints["PLAYER"] = Coord(x * Globals::SPRITE_SCALE, y * Globals::SPRITE_SCALE);
}

void Level::draw(Graphics &graphics) {
    for (const auto &tile : this->tiles) {
        tile->draw(graphics);
    }

    for (const auto &boundingBox: this->boundingBoxes) {
        boundingBox.draw(graphics);
    }

    for (const auto &slope: this->slopes) {
        slope.draw(graphics);
    }
}

void Level::update(unsigned elapsedTime) {
    for (auto &tile : this->tiles) {
        tile->update(elapsedTime);
    }
}


void Level::loadMap(Graphics &graphics) {
    // TODO 03-Feb-2019 blockost Find a way to load all maps before the game starts (like we do
    // for textures

    std::stringstream ss;
    ss << "../data/maps/" << this->mapName << ".json";

    std::ifstream ifs(ss.str());
    auto jsonFile = json::parse(ifs);

    // Retrieve map size (width, height)
    const unsigned mapWidth = jsonFile["width"];

    // Retrieve tilesets texture + size (width, height)
    const auto tilesets = jsonFile["tilesets"];
    for (const auto &t: tilesets) {

        // TODO 12-Feb-2019 blockost In Tiled, path to tilesets is relative to the map.
        // We should find a more elegant way for a workaround
        const std::string &texturePath = "../data/tilesets/" + t["image"].get<std::string>();
        unsigned firstGid = t["firstgid"];
        unsigned tilesetWidth = t["columns"];
        unsigned tilesetHeight = t["tilecount"].get<int>() / tilesetWidth;

        std::vector<TileAnimation> animations;

        // Checkin if this tileset contains animations
        if (t.find("tiles") != t.end()) {
            // Retrieve and store animation
            for (const auto &tile : t["tiles"]) {
                std::vector<std::pair<unsigned, unsigned>> animation;
                for (const auto &a : tile["animation"]) {
                    std::pair<unsigned, unsigned> pair{a["tileid"], a["duration"]};
                    animation.push_back(pair);
                }
                animations.emplace_back(TileAnimation(animation));
            }
        }

        Tileset tileset(texturePath, firstGid, tilesetWidth, tilesetHeight, animations);

        // Load texture and store it to the list of tilesets
        graphics.loadTexture(texturePath);
        this->tilesets.push_back(std::move(tileset));
    }

    const auto &layers = jsonFile["layers"];
    for (const auto &layer : layers) {

        if (layer["name"] == "collisions") {
            this->parseCollisionObjects(layer["objects"]);
        } else if (layer["name"] == "spawn points") {
            this->parseSpawnPointObjects(layer["objects"]);
        } else if (layer["name"] == "slopes") {
            this->parseSlopeObjects(layer["objects"]);
        } else {
            // Parse other layers (which should contain tiles only)
            const auto &data = layer["data"];
            unsigned tileCounter = 0;
            for (const auto &t : data) {
                // Only store tiles whose id != 0
                if (t != 0) {
                    const auto ts = this->getTilesetAssociatedToTileId(t);
                    unsigned int tileId = t.get<int>() - ts.getFirstTileId();
                    if (ts.hasAnimationForTile(tileId)) {
                        std::unique_ptr<Tile> tile(new AnimatedTile(tileId, tileCounter, ts, ts.getAnimationForTile(tileId)));
                        this->tiles.push_back(std::move(tile));
                    } else {
                        std::unique_ptr<Tile> tile(new Tile(tileId, tileCounter, ts));
                        this->tiles.push_back(std::move(tile));
                    }

                }
                tileCounter++;
            }
        }
    }

    for (auto &tile : this->tiles) {
        tile->setPositionInTileset();
        tile->setDestinationOnMap(mapWidth);
    }
}

void Level::parseCollisionObjects(const json &collisionObjects) {
    for (const auto &collisionObject: collisionObjects) {
        this->boundingBoxes.emplace_back(BoundingBox(collisionObject["x"],
                                                     collisionObject["y"],
                                                     collisionObject["width"],
                                                     collisionObject["height"]));
    }
}

void Level::parseSpawnPointObjects(const json &spawnPointObjects) {
    for (const auto &spawnPoint : spawnPointObjects) {
        if (spawnPoint["name"] == "Player") {
            this->setPlayerSpawnPoint(spawnPoint["x"], spawnPoint["y"]);
        }
    }
}

void Level::parseSlopeObjects(const json &slopeObjects) {
    for (const auto &slopeObject : slopeObjects) {
        const auto &startPoint = Coord(slopeObject["x"], slopeObject["y"]);
        const auto &polyline = slopeObject["polyline"];

        for (unsigned i = 0; i < polyline.size() - 1; i++) {
            const auto &p1 = Coord(startPoint.x + polyline.at(i)["x"].get<int>(),
                                   startPoint.y + polyline.at(i)["y"].get<int>());
            const auto &p2 = Coord(startPoint.x + polyline.at(i + 1)["x"].get<int>(),
                                   startPoint.y + polyline.at(i + 1)["y"].get<int>());

            const auto &slope = Slope(p1, p2);
            this->slopes.emplace_back(slope);
        }
    }
}

/**
 * To retrieve the associated tileset, we need to get the tileset with the higher firstgid but less
 * than the given gid.
 */
const Tileset Level::getTilesetAssociatedToTileId(unsigned gid) const {

    // TODO 03-Mar-2019 blockost Find a way to return a reference to the tileset, not a copy

    // XXX 03-Mar-2019 blockost
    // From https://stackoverflow.com/questions/21204676/modern-way-to-filter-stl-container
    std::vector<Tileset> candidateTilesets;

    // Retrieves the tilesets with firstgid <= id
    std::copy_if(this->tilesets.begin(), this->tilesets.end(),
                 std::back_inserter(candidateTilesets),
                 [gid](const Tileset &t) { return gid >= t.getFirstTileId(); });

    // Retrieve the tileset with the higher firstgid from the list of candidates
    const auto associatedTileset = std::max_element(candidateTilesets.begin(),
                                                    candidateTilesets.end(),
                                                    [](const Tileset &t1, const Tileset &t2) {
                                                        return t1.getFirstTileId() <
                                                               t2.getFirstTileId();
                                                    });

    if (associatedTileset == candidateTilesets.end()) {
        throw InvalidLevelException("No tileset found!");
    }

    return (*associatedTileset);
}
