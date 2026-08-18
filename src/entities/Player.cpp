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

void Player::update(
    float deltaTime,
    float screenWidth,
    float screenHeight,
    const std::vector<Platform>& platforms)
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

    //Guarda y anterior
    float previousY = y;

    //==========
    // Movimento
    //==========
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;

    //===============
    //Limites da tela
    //===============

    //Limite esquerdo
    if (x < 0.0f)
    {
        x = 0.0f;
    }

    // Limite direito
    if (x + width > screenWidth)
    {
        x = screenWidth - width;
    }

    // Limite superior
    // if (y < 0.0f)
    // {
    //     y = 0.0f;
    //
    //     if (velocityY < 0.0f)
    //     {
    //         velocityY = 0.0f;
    //     }
    // }

    //=======================
    //Colisão com Plataformas
    //=======================
    onGround = false;

    for (const Platform& platform : platforms) {
        const SDL_FRect& platformRect = platform.getRect();

        bool horizontalCollision = x + width > platformRect.x && x < platformRect.x + platformRect.w;

        bool wasAbove = previousY + height <= platformRect.y;

        bool isTouchingPlatform = y + height >= platformRect.y;

        if (velocityY >= 0.0f && horizontalCollision && wasAbove && isTouchingPlatform)
        {
            y = platformRect.y - height;
            velocityY = 0.0f;
            onGround = true;

            break;
        }
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

