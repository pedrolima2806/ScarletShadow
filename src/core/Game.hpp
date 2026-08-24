#ifndef SOMBRAESCARLATE_GAME_HPP
#define SOMBRAESCARLATE_GAME_HPP

#include <SDL3/SDL.h>
#include <memory>

#include "GameState.hpp"
#include "../entities/Player.hpp"
#include "../render/Camera.hpp"
#include "../world/Level.hpp"
#include "Menu.hpp"

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();

private:
    void startGame();
    void returnToMenu();

    void processEvents();
    void update();
    void render();

    void renderPlaying();
    void updatePlaying();

    GameState gameState;

    bool running;

    static constexpr int SCREEN_WIDTH = 640;
    static constexpr int SCREEN_HEIGHT = 480;

    SDL_Window *window;
    SDL_Renderer *renderer;

    TTF_Font *font;

    std::unique_ptr<Menu> menu;

    std::unique_ptr<Player> player;
    Camera camera;
    std::unique_ptr<Level> level;

    Uint64 lastTime;

};

#endif //SOMBRAESCARLATE_GAME_HPP
