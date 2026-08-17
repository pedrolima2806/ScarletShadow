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
    jumpBufferTimer(0.0f),
    jumpBufferDuration(0.12f)
{}

void Player::handleInput(const SDL_Event &event) {
    //Tecla Pressionada
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.scancode == SDL_SCANCODE_A)
        { movingLeft = true;}

        if (event.key.scancode == SDL_SCANCODE_D)
        { movingRight = true;}

        if (event.key.scancode == SDL_SCANCODE_SPACE &&
            !event.key.repeat)
        {
            jumpBufferTimer = jumpBufferDuration;
        }
    }

    //Tecla Solta
    if (event.type == SDL_EVENT_KEY_UP)
    {
        if (event.key.scancode == SDL_SCANCODE_A)
        { movingLeft = false;}

        if (event.key.scancode == SDL_SCANCODE_D)
        { movingRight = false;}
    }

    //Movimento Horizontal
    velocityX = 0.0f;

    if (movingLeft) { velocityX -= speed;}
    if (movingRight) { velocityX += speed;}
}

void Player::jump() {
    if (onGround)
    {
        velocityY = -jumpForce;
        onGround = false;
    }
}

void Player::update(float deltaTime) {
    // Evita que um frame absurdamente longo destrua a física
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    // -------------------------
    // Movimento horizontal
    // -------------------------

    velocityX = 0.0f;

    if (movingLeft)
    {
        velocityX -= speed;
    }

    if (movingRight)
    {
        velocityX += speed;
    }

    // -------------------------
    // Pulo
    // -------------------------

    // Se já estamos no chão e existe um pedido de pulo,
    // executamos ANTES de aplicar a física.
    if (onGround && jumpBufferTimer > 0.0f)
    {
        velocityY = -jumpForce;
        onGround = false;

        jumpBufferTimer = 0.0f;
    }

    // -------------------------
    // Gravidade
    // -------------------------

    velocityY += gravity * deltaTime;

    // -------------------------
    // Movimento
    // -------------------------

    x += velocityX * deltaTime;
    y += velocityY * deltaTime;

    // -------------------------
    // Solo
    // -------------------------

    const float groundY = 400.0f;

    onGround = false;

    if (y + height >= groundY)
    {
        y = groundY - height;
        velocityY = 0.0f;
        onGround = true;

        // O jogador apertou SPACE pouco antes de aterrissar?
        if (jumpBufferTimer > 0.0f)
        {
            velocityY = -jumpForce;
            onGround = false;

            jumpBufferTimer = 0.0f;
        }
    }

    // -------------------------
    // Atualiza jump buffer
    // -------------------------

    if (jumpBufferTimer > 0.0f)
    {
        jumpBufferTimer -= deltaTime;

        if (jumpBufferTimer < 0.0f)
        {
            jumpBufferTimer = 0.0f;
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

