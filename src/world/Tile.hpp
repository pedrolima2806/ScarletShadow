#ifndef SOMBRAESCARLATE_TILE_HPP
#define SOMBRAESCARLATE_TILE_HPP

#include <SDL3/SDL.h>

#include "../render/Camera.hpp"

enum class TileType {
    Empty,
    Solid,
    Hazard
};

class Tile {
public:
    Tile(float x, float y, float size, TileType type);

    void render (SDL_Renderer* renderer, const Camera& camera) const;

    const SDL_FRect& getRect() const;
    TileType getType() const;

    bool isSolid() const;

private:
    SDL_FRect rect;
    TileType type;
};

#endif //SOMBRAESCARLATE_TILE_HPP
