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
    jumpHeld(false)
{}

void Player::setPosition(float newX, float newY) {
    x = newX;
    y = newY;

    velocityX = 0.0f;
    velocityY = 0.0f;
}

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

    onGround = false;
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

SDL_FRect Player::getRect() const
{
    return {
        x,
        y,
        width,
        height
    };
}

float Player::getVelocityX() const
{
    return velocityX;
}

float Player::getVelocityY() const
{
    return velocityY;
}

void Player::moveX(float amount)
{
    x += amount;
}

void Player::moveY(float amount)
{
    y += amount;
}

void Player::resolveHorizontalCollision(float newX)
{
    x = newX;
    velocityX = 0.0f;
}

void Player::resolveVerticalCollision(
    float newY,
    bool grounded
)
{
    y = newY;
    velocityY = 0.0f;
    onGround = grounded;
}