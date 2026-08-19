#ifndef SOMBRAESCARLATE_PLAYER_HPP
#define SOMBRAESCARLATE_PLAYER_HPP

#include "SDL3/SDL_render.h"

class Player {
public:
    Player(float x, float y);

    void setPosition(float newX, float newY);

    void handleInput(const SDL_Event &event);

    void update(float deltaTime);
    void render(SDL_Renderer* renderer);

    SDL_FRect getRect() const;

    float getVelocityX() const;
    float getVelocityY() const;

    void moveX(float amount);
    void moveY(float amount);

    void resolveHorizontalCollision(float newX);
    void resolveVerticalCollision(float newY, bool grounded);

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
