#include "Platform.hpp"

Platform::Platform(float x, float y, float width, float height) {
    rect = {
        x,
        y,
        width,
        height
    };
}

void Platform::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &rect);
}

const SDL_FRect& Platform::getRect() const {
    return rect;
}