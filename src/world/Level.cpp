#include "Level.hpp"

Level::Level() {
    constexpr float TILE_SIZE = 30.0f;
    tiles.emplace_back(
       100.0f,
       280.0f,
       TILE_SIZE,
       TileType::Solid
   );

    tiles.emplace_back(
        140.0f,
        280.0f,
        TILE_SIZE,
        TileType::Hazard
    );

    tiles.emplace_back(
        180.0f,
        280.0f,
        TILE_SIZE,
        TileType::Solid
    );

    platforms.emplace_back(
        0.0f,
        470.0f,
        1280.0f,
        20.0f
    );

    platforms.emplace_back(
        100.0f,
        400.0f,
        250.0f,
        20.0f
    );

    platforms.emplace_back(
        300.0f,
        340.0f,
        200.0f,
        20.0f
    );
}

void Level::render(SDL_Renderer *renderer) const {
    for (const Tile& tile : tiles) {
        tile.render(renderer);
    }

    for (const Platform &platform : platforms) {
        platform.render(renderer);
    }
}

const std::vector<Platform> &Level::getPlatforms() const {
    return platforms;
}

const std::vector<Tile> &Level::getTiles() const {
    return tiles;
}
