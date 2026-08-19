#ifndef SOMBRAESCARLATE_LEVEL_HPP
#define SOMBRAESCARLATE_LEVEL_HPP

#include <vector>
#include <string>

#include "entities/Platform.hpp"
#include "../world/Tile.hpp"

class Level {
public:
    Level();

    bool loadFromFile(const std::string& filePath);

    void render(SDL_Renderer *renderer) const;

    const std::vector<Platform> &getPlatforms() const;
    const std::vector<Tile> &getTiles() const;

    const SDL_FPoint& getSpawn() const;

private:
    static constexpr float TILE_SIZE = 40.0f;

    std::vector<Platform> platforms;
    std::vector<Tile> tiles;

    SDL_FPoint spawnPoint;
};

#endif //SOMBRAESCARLATE_LEVEL_HPP
