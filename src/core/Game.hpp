#ifndef SOMBRAESCARLATE_GAME_HPP
#define SOMBRAESCARLATE_GAME_HPP

#include <SDL3/SDL.h>

#include "../entities/Player.hpp"

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();

private:
    void processEvents();
    void update();
    void render();

    bool running;

    SDL_Window *window;
    SDL_Renderer *renderer;

    Player player;

    Uint64 lastTime;
};

#endif //SOMBRAESCARLATE_GAME_HPP
