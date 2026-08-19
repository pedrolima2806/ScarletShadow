#ifndef SOMBRAESCARLATE_COLLISIONSYSTEM_HPP
#define SOMBRAESCARLATE_COLLISIONSYSTEM_HPP
#include "entities/Player.hpp"
#include "world/Level.hpp"

class CollisionSystem {
public:
    static void resolvePlayerCollisions(Player& player, const Level& level, float deltaTime);
    static bool isPlayerTouchingHazard(const Player& player, const Level& level);

private:

};

#endif //SOMBRAESCARLATE_COLLISIONSYSTEM_HPP
