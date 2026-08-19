#include "Platform.hpp"

Platform::Platform(float x, float y, float width, float height) {
    rect = {
        x,
        y,
        width,
        height
    };
}

void Platform::render(SDL_Renderer* renderer, const Camera& camera) const {
    SDL_FRect renderRect{
        rect.x - camera.getX(),
        rect.y - camera.getY(),
        rect.w,
        rect.h
    };

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

    SDL_RenderFillRect(renderer, &renderRect);
}

const SDL_FRect& Platform::getRect() const {
    return rect;
}