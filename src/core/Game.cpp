#include "Game.hpp"

#include <iostream>
#include <ostream>

Game::Game()
    :running(false), window(nullptr), renderer(nullptr){}

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
            1280,
            720,
            0,
            &window,
            &renderer))
    {
        std::cerr << "Erro ao criar janela ou renderer: " << SDL_GetError() << std::endl;
        return false;
    }
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
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

//Update
void Game::update() {

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
    SDL_RenderPresent(renderer);
}
