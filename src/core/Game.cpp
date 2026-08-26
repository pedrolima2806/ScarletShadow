#include "Game.hpp"

#include <iostream>
#include <ostream>
#include <SDL3_image/SDL_image.h>

#include "physics/CollisionSystem.hpp"

Game::Game()
    : deltaTime(0.0f),
      gameState(GameState::MENU),
      running(false),
      window(nullptr),
      renderer(nullptr),
      fontMenu(nullptr),
      logoTexture(nullptr),
      menu(nullptr),
      camera(
          static_cast<float>(SCREEN_WIDTH),
          static_cast<float>(SCREEN_HEIGHT)),
      lastTime(0) {
}

Game::~Game() {
    if (renderer != nullptr) SDL_DestroyRenderer(renderer);
    if (window != nullptr) SDL_DestroyWindow(window);
    TTF_Quit();
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

    //Fonte usada pelo jogo
    if (!TTF_Init()) {
        std::cerr << "Erro ao iniciar SDL_ttf:" << SDL_GetError() << std::endl;
    }
    fontMenu = TTF_OpenFont("../assets/fonts/Cinzel/Cinzel-VariableFont_wght.ttf", SCREEN_HEIGHT/24.0f);
    if(!fontMenu)
    {
        std::cerr << "Erro carregando fonte.\n";
        return false;
    }

    logoTexture = IMG_LoadTexture(renderer,"../assets/sprites/menu/Menu_Logo.png");
    if (!logoTexture) {
        std::cerr << "Erro carregando logo:" << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Texture* menuBackgroundTexture = IMG_LoadTexture(renderer, "../assets/sprites/menu/Menu_Background.png");

    SDL_Texture* menuMarkerTexture = IMG_LoadTexture(renderer, "../assets/sprites/menu/Menu_Marker.png");

    menu = std::make_unique<Menu>(fontMenu, logoTexture, menuBackgroundTexture, menuMarkerTexture);

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

//Lógica do menu
void Game::startGame() {
    level = std::make_unique<Level>();
    player = std::make_unique<Player>(100.0f,100.0f);

    if (!level->loadFromFile("../assets/maps/level_03.map")){
        std::cerr << "Falha ao carregar a fase." << std::endl;
        return;
    }

    const SDL_FPoint& spawn = level->getSpawn();
    player->setPosition(spawn);

    gameState = GameState::PLAYING;
}

void Game::returnToMenu() {


    gameState = GameState::MENU;

}

//Processa os eventos
void Game::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
        if (gameState == GameState::MENU) {
            MenuAction action = menu->handleEvent(event);

            switch(action)
            {
                case MenuAction::START_GAME:
                    startGame();
                    break;

                case MenuAction::OPTIONS:
                    break;

                case MenuAction::EXIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }
        else if (gameState == GameState::PLAYING) {
            player->handleInput(event);
        }
    }
}

//======
//Update
//======
void Game::update() {
    Uint64 currentTime = SDL_GetTicks();

    float deltaTime = static_cast<float>(currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;


    switch (gameState) {
        case GameState::MENU:
            menu->updateMenu(deltaTime);
            break;
        case GameState::PLAYING:
            updatePlaying(deltaTime);
            break;
        default:
            break;
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

    switch (gameState) {
        case GameState::MENU:
            menu->renderMenu(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
        case GameState::PLAYING:
            renderPlaying();
            break;
        case GameState::RUNNING:
            break;
        case GameState::PAUSED:
            break;
    }

    SDL_RenderPresent(renderer);
}

void Game::renderPlaying() {
    level->render(renderer, camera);
    player->render(renderer, camera);
}

void Game::updatePlaying(float deltaTime) {
    player->update(deltaTime);

    CollisionSystem::resolvePlayerCollisions(
        *player,
        *level,
        deltaTime,
        static_cast<float>(SCREEN_WIDTH),
        static_cast<float>(SCREEN_HEIGHT)
    );

    //Lógica de retornar ao Spawn
    SDL_FRect playerRect = player->getRect();

    bool fellOutOfScreen = playerRect.y > level->getWorldHeight();
    bool touchedHazard = CollisionSystem::isPlayerTouchingHazard(*player, *level);

    if (fellOutOfScreen || touchedHazard) {
        const SDL_FPoint& spawn = level->getSpawn();
        player->setPosition(spawn);
    }

    camera.follow(
        player->getRect(),
        level->getWorldWidth(),
        level->getWorldHeight()
    );
}
