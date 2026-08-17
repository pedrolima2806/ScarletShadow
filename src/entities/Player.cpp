#include "Player.hpp"

Player::Player(float x, float y):
    x(x),
    y(y),
    velocityX(0.0f),
    velocityY(0.0f),
    width(25.0f),
    height(25.0f),
    speed(300.0f),
    gravity(1500.0f),
    jumpForce(500.0f),
    onGround(false),
    movingLeft(false),
    movingRight(false),
    jumpHeld(false),
    jumpBufferTimer(0.0f),
    jumpBufferDuration(0.12f)
{}

void Player::handleInput(const SDL_Event& event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.scancode == SDL_SCANCODE_A)
        {
            movingLeft = true;
        }

        if (event.key.scancode == SDL_SCANCODE_D)
        {
            movingRight = true;
        }

        if (event.key.scancode == SDL_SCANCODE_SPACE)
        {
            jumpHeld = true;
        }
    }

    if (event.type == SDL_EVENT_KEY_UP)
    {
        if (event.key.scancode == SDL_SCANCODE_A)
        {
            movingLeft = false;
        }

        if (event.key.scancode == SDL_SCANCODE_D)
        {
            movingRight = false;
        }

        if (event.key.scancode == SDL_SCANCODE_SPACE)
        {
            jumpHeld = false;
        }
    }
}

void Player::jump() {
    if (onGround)
    {
        velocityY = -jumpForce;
        onGround = false;
    }
}

void Player::update(float deltaTime)
{
    // Movimento horizontal
    velocityX = 0.0f;

    if (movingLeft)
    {
        velocityX -= speed;
    }

    if (movingRight)
    {
        velocityX += speed;
    }

    // Pulo
    if (jumpHeld && onGround)
    {
        velocityY = -jumpForce;
        onGround = false;
    }

    // Gravidade
    velocityY += gravity * deltaTime;

    // Movimento
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;

    // Solo
    const float groundY = 400.0f;

    if (y + height >= groundY)
    {
        y = groundY - height;
        velocityY = 0.0f;
        onGround = true;
    }
    else
    {
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

