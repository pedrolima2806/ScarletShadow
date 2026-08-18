#ifndef SOMBRAESCARLATE_PLAYER_HPP
#define SOMBRAESCARLATE_PLAYER_HPP
#include <vector>

#include "SDL3/SDL_render.h"
#include "../entities/Platform.hpp"
#include "../world/Tile.hpp"

class Player {
public:
    Player(float x, float y);

    void setPosition(float newX, float newY);

    void handleInput(const SDL_Event &event);

    void update(float deltaTime,
                float screenWidth,
                float screenHeight,
                const std::vector<Platform>& platforms,
                const std::vector<Tile>& tiles
                );
    void render(SDL_Renderer* renderer);

    bool isTouchingHazard(const std::vector<Tile>& tiles) const;

private:
    float x;
    float y;

    float velocityX;
    float velocityY;

    float width;
    float height;

    float speed;
    float gravity;
    float jumpForce;

    bool onGround;
    bool movingLeft;
    bool movingRight;
    bool jumpHeld;
};

#endif //SOMBRAESCARLATE_PLAYER_HPP
