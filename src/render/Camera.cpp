#include "Camera.hpp"

Camera::Camera(float width, float height)
    : x(0.0f), y(0.0f), width(width), height(height) {}

void Camera::follow(const SDL_FRect &target, float worldWidth, float worldHeight)
{
    // Centralizar câmera no player
    x = target.x + target.w / 2.0f - width / 2.0f;
    y = target.y + target.h / 2.0f - height / 2.0f;

    //=================
    // Limites da câmera
    //=================
    // Limite esquerdo
    if (x < 0.0f)
    {
        x = 0.0f;
    }

    // Limite superior
    if (y < 0.0f)
    {
        y = 0.0f;
    }

    // Limite direito
    if (x + width > worldWidth)
    {
        x = worldWidth - width;
    }

    // Limite inferior
    if (y + height > worldHeight)
    {
        y = worldHeight - height;
    }

    // Fase menor que a camera
    if (worldWidth < width)
    {
        x = 0.0f;
    }
    if (worldHeight < height)
    {
        y = 0.0f;
    }
}

float Camera::getX() const
{
    return x;
}

float Camera::getY() const
{
    return y;
}
