#ifndef SOMBRAESCARLATE_PLATFORM_HPP
#define SOMBRAESCARLATE_PLATFORM_HPP

#include "SDL3/SDL_render.h"

#include "render/Camera.hpp"

class Platform {
public:
    Platform(float x, float y, float width, float height);

    void render(SDL_Renderer* renderer, const Camera& camera) const;

    const SDL_FRect& getRect() const;

private:
    SDL_FRect rect;
};


#endif //SOMBRAESCARLATE_PLATFORM_HPP
