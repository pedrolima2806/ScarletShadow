#include "CollisionSystem.hpp"

void CollisionSystem::resolvePlayerCollisions(
    Player& player,
    const Level& level,
    float deltaTime,
    float screenWidth,
    float screenHeight
)
{
    // =========================================================
    // Movimento horizontal
    // =========================================================

    float velocityX = player.getVelocityX();

    player.moveX(velocityX * deltaTime);

    // ---------------------------------------------------------
    // Colisão horizontal com Tiles sólidos
    // ---------------------------------------------------------

    for (const Tile& tile : level.getTiles())
    {
        if (!tile.isSolid())
        {
            continue;
        }

        SDL_FRect playerRect = player.getRect();
        const SDL_FRect& tileRect = tile.getRect();

        bool collision =
            playerRect.x < tileRect.x + tileRect.w &&
            playerRect.x + playerRect.w > tileRect.x &&
            playerRect.y < tileRect.y + tileRect.h &&
            playerRect.y + playerRect.h > tileRect.y;

        if (!collision)
        {
            continue;
        }

        // Player indo para direita
        if (velocityX > 0.0f)
        {
            player.resolveHorizontalCollision(
                tileRect.x - playerRect.w
            );
        }

        // Player indo para esquerda
        else if (velocityX < 0.0f)
        {
            player.resolveHorizontalCollision(
                tileRect.x + tileRect.w
            );
        }

        break;
    }

    // ---------------------------------------------------------
    // Limites horizontais da janela
    // ---------------------------------------------------------

    SDL_FRect playerRect = player.getRect();

    // Borda esquerda
    if (playerRect.x < 0.0f)
    {
        player.resolveHorizontalCollision(0.0f);
    }

    playerRect = player.getRect();

    // Borda direita
    if (playerRect.x + playerRect.w > level.getWorldWidth())
    {
        player.resolveHorizontalCollision(
            screenWidth - playerRect.w
        );
    }


    // =========================================================
    // Movimento vertical
    // =========================================================

    SDL_FRect beforeVertical = player.getRect();

    float velocityY = player.getVelocityY();

    player.moveY(velocityY * deltaTime);

    bool verticalResolved = false;


    // ---------------------------------------------------------
    // Colisão vertical com Tiles sólidos
    // ---------------------------------------------------------

    for (const Tile& tile : level.getTiles())
    {
        if (!tile.isSolid())
        {
            continue;
        }

        playerRect = player.getRect();

        const SDL_FRect& tileRect = tile.getRect();

        bool collision =
            playerRect.x < tileRect.x + tileRect.w &&
            playerRect.x + playerRect.w > tileRect.x &&
            playerRect.y < tileRect.y + tileRect.h &&
            playerRect.y + playerRect.h > tileRect.y;

        if (!collision)
        {
            continue;
        }

        // Player caindo
        if (velocityY > 0.0f)
        {
            player.resolveVerticalCollision(
                tileRect.y - playerRect.h,
                true
            );
        }

        // Player subindo
        else if (velocityY < 0.0f)
        {
            player.resolveVerticalCollision(
                tileRect.y + tileRect.h,
                false
            );
        }

        verticalResolved = true;

        break;
    }


    // =========================================================
    // Colisão com Platforms
    // Apenas por cima
    // =========================================================

    if (!verticalResolved)
    {
        float previousBottom =
            beforeVertical.y + beforeVertical.h;

        for (const Platform& platform : level.getPlatforms())
        {
            playerRect = player.getRect();

            const SDL_FRect& platformRect =
                platform.getRect();

            bool horizontalOverlap =
                playerRect.x + playerRect.w > platformRect.x &&
                playerRect.x < platformRect.x + platformRect.w;

            bool wasAbove =
                previousBottom <= platformRect.y;

            bool reachedPlatform =
                playerRect.y + playerRect.h >= platformRect.y;

            if (
                velocityY >= 0.0f &&
                horizontalOverlap &&
                wasAbove &&
                reachedPlatform
            )
            {
                player.resolveVerticalCollision(
                    platformRect.y - playerRect.h,
                    true
                );

                verticalResolved = true;

                break;
            }
        }
    }


    // =========================================================
    // Limites verticais da janela
    // =========================================================

    // playerRect = player.getRect();
    //
    // // Teto
    // if (playerRect.y < 0.0f)
    // {
    //     player.resolveVerticalCollision(
    //         0.0f,
    //         false
    //     );
    // }
    //
    // playerRect = player.getRect();
    //
    // // Fundo
    // if (playerRect.y + playerRect.h > level.getWorldHeight())
    // {
    //     player.resolveVerticalCollision(
    //         screenHeight - playerRect.h,
    //         true
    //     );
    // }
}


bool CollisionSystem::isPlayerTouchingHazard(const Player &player, const Level &level)
{
    //aumentar área de dano do hazard tile
    // constexpr float HAZARD_MARGIN = 4.0f;
    //
    SDL_FRect playerRect = player.getRect();
    //
    // playerRect.x -= HAZARD_MARGIN;
    // playerRect.y -= HAZARD_MARGIN;
    //
    // playerRect.w += HAZARD_MARGIN * 2.0f;
    // playerRect.h += HAZARD_MARGIN * 2.0f;

    for (const Tile& tile : level.getTiles())
    {
        if (tile.getType() != TileType::Hazard)
        {
            continue;
        }

        const SDL_FRect& tileRect = tile.getRect();

        bool collision =
            playerRect.x < tileRect.x + tileRect.w &&
            playerRect.x + playerRect.w > tileRect.x &&
            playerRect.y < tileRect.y + tileRect.h &&
            playerRect.y + playerRect.h > tileRect.y;

        if (collision)
        {
            return true;
        }
    }

    return false;
}
