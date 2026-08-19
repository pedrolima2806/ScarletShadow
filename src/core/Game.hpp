#ifndef SOMBRAESCARLATE_GAME_HPP
#define SOMBRAESCARLATE_GAME_HPP

#include <SDL3/SDL.h>

#include "../entities/Player.hpp"
#include "../render/Camera.hpp"
#include "../world/Level.hpp"

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

    static constexpr int SCREEN_WIDTH = 640;
    static constexpr int SCREEN_HEIGHT = 480;

    SDL_Window *window;
    SDL_Renderer *renderer;

    Player player;
    Camera camera;
    Level level;

    Uint64 lastTime;
};

#endif //SOMBRAESCARLATE_GAME_HPP
