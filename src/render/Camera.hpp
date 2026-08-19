#ifndef SOMBRAESCARLATE_CAMERA_HPP
#define SOMBRAESCARLATE_CAMERA_HPP
#include "SDL3/SDL_rect.h"

class Camera {
public:
    Camera(float width, float height);

    void follow(
        const SDL_FRect &target,
        float worldWidth,
        float worldHeight);

    float getX() const;
    float getY() const;

private:
    float x;
    float y;

    float width;
    float height;
};

#endif //SOMBRAESCARLATE_CAMERA_HPP
