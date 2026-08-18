#ifndef SOMBRAESCARLATE_LEVEL_HPP
#define SOMBRAESCARLATE_LEVEL_HPP

#include <SDL3/SDL.h>
#include <vector>

#include "entities/Platform.hpp"

class Level {
public:
    Level();

    void render(SDL_Renderer *renderer) const;

    const std::vector<Platform> &getPlatforms() const;

private:
    std::vector<Platform> platforms;
    //std::vector<std::vector<Tile>> tiles;
};

#endif //SOMBRAESCARLATE_LEVEL_HPP
