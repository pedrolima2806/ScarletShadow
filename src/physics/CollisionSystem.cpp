#include "CollisionSystem.hpp"

#include "CollisionSystem.hpp"

void CollisionSystem::resolvePlayerCollisions(
    Player& player,
    const Level& level,
    float deltaTime
)
{
    // =====================
    // Movimento horizontal
    // =====================

    float velocityX = player.getVelocityX();

    player.moveX(velocityX * deltaTime);

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

        if (velocityX > 0.0f)
        {
            player.resolveHorizontalCollision(
                tileRect.x - playerRect.w
            );
        }
        else if (velocityX < 0.0f)
        {
            player.resolveHorizontalCollision(
                tileRect.x + tileRect.w
            );
        }

        break;
    }

    // ===================
    // Movimento vertical
    // ===================

    SDL_FRect beforeVertical = player.getRect();

    float velocityY = player.getVelocityY();

    player.moveY(velocityY * deltaTime);

    bool verticalResolved = false;

    // =====================
    // Tiles sólidos
    // =====================

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

        if (velocityY > 0.0f)
        {
            player.resolveVerticalCollision(
                tileRect.y - playerRect.h,
                true
            );
        }
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

    // =====================
    // Platforms one-way
    // =====================

    if (!verticalResolved)
    {
        float previousBottom =
            beforeVertical.y + beforeVertical.h;

        for (const Platform& platform :
             level.getPlatforms())
        {
            SDL_FRect playerRect =
                player.getRect();

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

                break;
            }
        }
    }
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
