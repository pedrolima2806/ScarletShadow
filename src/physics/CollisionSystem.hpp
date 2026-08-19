#ifndef SOMBRAESCARLATE_COLLISIONSYSTEM_HPP
#define SOMBRAESCARLATE_COLLISIONSYSTEM_HPP
#include "entities/Player.hpp"
#include "world/Level.hpp"

class CollisionSystem {
public:
    static void resolvePlayerCollisions(Player& player, const Level& level, float deltaTime, float screenWidth, float screenHeight);
    static bool isPlayerTouchingHazard(const Player& player, const Level& level);

private:

};

#endif //SOMBRAESCARLATE_COLLISIONSYSTEM_HPP
