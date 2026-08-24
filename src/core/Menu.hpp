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
    Menu(TTF_Font* font);

    MenuAction handleEvent(SDL_Event &event);
    void updateMenu();
    void renderMenu(SDL_Renderer* renderer);

    void moveSelection(int direction);

    void renderText(SDL_Renderer* renderer,
        const std::string& text,
        SDL_Color color,
        float x,
        float y);

private:
    int selectedOption;
    std::vector<MenuOption> options;

    TTF_Font* font;
};

#endif //SOMBRAESCARLATE_MENU_HPP
