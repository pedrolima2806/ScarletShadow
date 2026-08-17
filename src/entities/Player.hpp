#ifndef SOMBRAESCARLATE_PLAYER_HPP
#define SOMBRAESCARLATE_PLAYER_HPP
#include "SDL3/SDL_render.h"

class Player {
public:
    Player(float x, float y);

    void handleInput(const SDL_Event &event);
    void jump();

    void update(float deltaTime);
    void render(SDL_Renderer* renderer);

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

    float jumpBufferTimer;
    float jumpBufferDuration;

    bool onGround;
    bool movingLeft;
    bool movingRight;
};

#endif //SOMBRAESCARLATE_PLAYER_HPP
