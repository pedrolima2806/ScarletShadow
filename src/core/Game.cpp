#include "Game.hpp"

#include <iostream>
#include <ostream>

Game::Game()
    : running(false),
      window(nullptr),
      renderer(nullptr),
      player(100.f, 100.f),
      lastTime(0)
{
}

Game::~Game() {
    if (renderer != nullptr) SDL_DestroyRenderer(renderer);
    if (window != nullptr) SDL_DestroyWindow(window);
    SDL_Quit();
}

//Inicia SDL, window e renderer e confere erros
bool Game::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erro ao iniciar SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    if (!SDL_CreateWindowAndRenderer(
            "Sombra Escarlate",
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0,
            &window,
            &renderer))
    {
        std::cerr << "Erro ao criar janela ou renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    running = true;
    lastTime = SDL_GetTicks();

    return true;
}

//Loop
void Game::run() {
    while (running) {
        processEvents();
        update();
        render();
    }
}

//Processa os eventos
void Game::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
        player.handleInput(event);
    }
}

//Update
void Game::update() {
    Uint64 currentTime = SDL_GetTicks();

    float deltaTime = static_cast<float>(currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    player.update(deltaTime,
                  static_cast<float>(SCREEN_WIDTH),
                  static_cast<float>(SCREEN_HEIGHT),
                  level.getPlatforms(),
                  level.getTiles()
                  );

    if (player.isTouchingHazard(level.getTiles())) {
        player.setPosition(level.getSpawnX(), level.getSpawnY());
    }
}

//Renderização
void Game::render() {
    SDL_SetRenderDrawColor(
        renderer,
        20,
        20,
        30,
        255
    );

    SDL_RenderClear(renderer);

    level.render(renderer);
    player.render(renderer);

    SDL_RenderPresent(renderer);
}
