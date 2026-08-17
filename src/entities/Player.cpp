#include "Player.hpp"

Player::Player(float x, float y):
    x(x),
    y(y),
    velocityX(0.0f),
    velocityY(0.0f),
    width(25.0f),
    height(25.0f),
    speed(300.0f)
{}

void Player::handleInput() {
    velocityX = 0.0f;
    const bool* keyboardState = SDL_GetKeyboardState(nullptr);

    if (keyboardState[SDL_SCANCODE_A]) {velocityX = -speed;}
    if (keyboardState[SDL_SCANCODE_D]) {velocityX = speed;}
}

void Player::update(float deltaTime) {
    //Gravidade
    velocityY += gravity * deltaTime;

    //Movimento
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;

    //Solo
    const float groundY = 400.0f;

    if (y +height >= groundY) {
        y = groundY - height;
        velocityY = 0.0f;
        onGround = true;
    }
    else {
        onGround = false;
    }
}

void Player::render(SDL_Renderer* renderer) {
    SDL_FRect rect{
        x,
        y,
        width,
        height
    };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

