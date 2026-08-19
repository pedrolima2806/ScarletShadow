#include "Tile.hpp"

Tile::Tile(float x, float y, float size, TileType type)
    : rect(x, y, size, size),
      type(type)
{
}

void Tile::render(SDL_Renderer* renderer, const Camera& camera) const {
    switch (type) {
        case TileType::Solid:
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            break;
        case TileType::Hazard:
            SDL_SetRenderDrawColor(renderer, 190, 100, 100, 255);
            break;
        default:
            return;
    }

    SDL_FRect renderRect{
        rect.x - camera.getX(),
        rect.y - camera.getY(),
        rect.w,
        rect.h
    };

    SDL_RenderFillRect(renderer, &renderRect);
}

const SDL_FRect& Tile::getRect() const {
    return rect;
}

TileType Tile::getType() const {
    return type;
}

bool Tile::isSolid() const {
    return type == TileType::Solid;
}