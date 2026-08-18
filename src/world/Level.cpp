#include "Level.hpp"

Level::Level() {
    platforms.emplace_back(
        0.0f,
        470.0f,
        1280.0f,
        20.0f
    );

    platforms.emplace_back(
        100.0f,
        400.0f,
        250.0f,
        20.0f
    );

    platforms.emplace_back(
        300.0f,
        340.0f,
        200.0f,
        20.0f
    );
}

void Level::render(SDL_Renderer *renderer) const {
    for (const Platform &platform : platforms) {
        platform.render(renderer);
    }
}

const std::vector<Platform> &Level::getPlatforms() const {
    return platforms;
}
