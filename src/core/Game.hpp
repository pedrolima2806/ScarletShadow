#ifndef SOMBRAESCARLATE_GAME_HPP
#define SOMBRAESCARLATE_GAME_HPP

#include <SDL3/SDL.h>

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
};

#endif //SOMBRAESCARLATE_GAME_HPP
