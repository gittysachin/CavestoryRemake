//
// Created by blockost on 2/4/19.
//

#include <cmath>
#include "Tile.h"

Tile::Tile(unsigned id, unsigned positionInJson, const Tileset &tileset)
        : id(id), positionInJson(positionInJson), tileset(tileset) {
}

Tile::~Tile() = default;

std::ostream &operator<<(std::ostream &ostream, const Tile &tile) {
    ostream << "id: " << tile.id << " positionInJson: " << tile.positionInJson
            << " sourceInTileset: " << tile.sourceInTileset << " destinationOnMap: "
            << tile.destinationOnMap;
    return ostream;
}

void Tile::setPositionInTileset() {
    this->sourceInTileset.x = this->id % this->tileset.getWidth() * Globals::SPRITE_WIDTH;
    this->sourceInTileset.y = this->id / this->tileset.getWidth() * Globals::SPRITE_HEIGHT;
}

void Tile::setDestinationOnMap(unsigned int mapWidth) {
    this->destinationOnMap.x = this->positionInJson % mapWidth * Globals::SPRITE_WIDTH *
                               Globals::SPRITE_SCALE;
    this->destinationOnMap.y = this->positionInJson / mapWidth * Globals::SPRITE_HEIGHT *
                               Globals::SPRITE_SCALE;
}

void Tile::draw(Graphics &graphics) const {
    SDL_Rect sourceRect = {this->sourceInTileset.x,
                           this->sourceInTileset.y, Globals::SPRITE_WIDTH,
                           Globals::SPRITE_HEIGHT};
    SDL_Rect destRect = {this->destinationOnMap.x, this->destinationOnMap.y,
                         Globals::SPRITE_WIDTH * Globals::SPRITE_SCALE,
                         Globals::SPRITE_HEIGHT * Globals::SPRITE_SCALE};

    SDL_Texture *texture = graphics.getTexture(this->tileset.getTexturePath());
    graphics.copyTextureToRenderer(texture, &sourceRect, &destRect);
}

void Tile::update(unsigned elapsedTime) {
    // no-op
}
