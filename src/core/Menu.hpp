#ifndef SOMBRAESCARLATE_MENU_HPP
#define SOMBRAESCARLATE_MENU_HPP

#include <vector>
#include <string>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"

enum class MenuAction {
    NONE,
    START_GAME,
    OPTIONS,
    EXIT
};

struct MenuOption {
    std::string text;
    MenuAction action;
};

class Menu {
public:
    Menu(TTF_Font* font, SDL_Texture* logo, SDL_Texture* backgroundTexture);

    MenuAction handleEvent(SDL_Event &event);
    void renderMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    void updateMenu(float deltaTime);

    void moveSelection(int direction);

    float getTextWidth(const std::string& text);
    float getTextHeight(const std::string& text);

    void renderLogo(SDL_Renderer* renderer, int screenWidth, int screenHeight, float x, float y);
    void renderText(SDL_Renderer* renderer, const std::string& text, SDL_Color color, float x, float y);
    void renderMarker(SDL_Renderer* renderer, const std::string& text, SDL_Color color, float x, float y);

private:
    int selectedOption;
    std::vector<MenuOption> options;

    TTF_Font* font;
    SDL_Texture* logoTexture;
    SDL_Texture* backgroundTexture;

    float markerWidth;
    float markerHeight;

    //Animação
    SDL_FRect logoAnimationLoop();

    int currentFrame;
    float frameTimer;
    float frameDuration;

    int frameWidth;
    int frameHeight;
};

#endif //SOMBRAESCARLATE_MENU_HPP
