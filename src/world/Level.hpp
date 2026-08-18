#ifndef SOMBRAESCARLATE_LEVEL_HPP
#define SOMBRAESCARLATE_LEVEL_HPP

#include <vector>

#include "entities/Platform.hpp"
#include "../world/Tile.hpp"

class Level {
public:
    Level();

    void render(SDL_Renderer *renderer) const;

    const std::vector<Platform> &getPlatforms() const;
    const std::vector<Tile> &getTiles() const;

private:
    std::vector<Platform> platforms;
    std::vector<Tile> tiles;
};

#endif //SOMBRAESCARLATE_LEVEL_HPP
