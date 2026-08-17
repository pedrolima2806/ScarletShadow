#include <chrono>
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "core/Game.hpp"

int main() {
    Game game;
    if (!game.init()) {
        return 1;
    }

    game.run();

    return 0;
}