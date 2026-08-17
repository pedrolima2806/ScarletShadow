#include <chrono>
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>


int main() {
    //=============
    //INICIALIZAÇÃO
    //=============
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (!TTF_Init()) {
        std::cerr << "TTF_Init failed." << std::endl;
    }
    //=================
    //WINDOW E RENDERER
    //=================
    int width = 640, height = 480;
    SDL_Window *window = SDL_CreateWindow("hellcat_mp", width, height, 0);
    if (!window) {
        std::cerr << "Failed to create window:" << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "Failed to create renderer:" << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //=====
    //FONTE
    //=====
    TTF_Font *font = TTF_OpenFont("../assets/fonts/Prata/Prata-Regular.ttf", 16);
    if (!font) {
        std::cerr << "Failed to open font:" << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //==========
    //LOOP CYCLE
    //==========
    auto previousTime = std::chrono::steady_clock::now();
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                running = false;
                }
            //====================
            //HANDLE EVENT SECTION
            //====================
            //musicPlayer.handleEvent(event);
        }
        //BACKGROUND
        SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
        SDL_RenderClear(renderer);

        //TEXT RENDERING

        //DELTA MS

        //==============
        //UPDATE SECTION
        //==============
        //musicPlayer.update(deltaMs);

        //=================
        //RENDERING SECTION
        //=================
        //musicPlayer.render(renderer, musicPlayerTexture);

        //===========================
        //ANIMATION RENDERING SECTION
        //===========================

        SDL_RenderPresent(renderer);
    }
    //============
    //FINALIZATION
    //============

    //MIX_DestroyMixer(mixer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    //MIX_Quit();
    SDL_Quit();

    return 0;
}