#include "Menu.hpp"

#include <iostream>

#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"

Menu::Menu(TTF_Font* font):
    selectedOption(0),
    font(font)
{
    options.emplace_back("Jogar", MenuAction::START_GAME);
    options.emplace_back("Opções", MenuAction::OPTIONS);
    options.emplace_back("Sair", MenuAction::EXIT);
}

MenuAction Menu::handleEvent(SDL_Event& event)
{
    if (event.type != SDL_EVENT_KEY_DOWN)
        return MenuAction::NONE;

    switch (event.key.scancode)
    {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
            moveSelection(-1);
            break;

        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
            moveSelection(1);
            break;

        case SDL_SCANCODE_SPACE:
        case SDL_SCANCODE_RETURN:
            return options[selectedOption].action;

        case SDL_SCANCODE_ESCAPE:
            return MenuAction::EXIT;

        default:
            break;
    }
    return MenuAction::NONE;
}

void Menu::updateMenu() {

}

void Menu::renderMenu(SDL_Renderer* renderer)
{
    float startX = 280.0f;
    float startY = 200.0f;
    float spacing = 60.0f;

    for(int i = 0; i < options.size(); i++)
    {
        float x = startX;
        float y = startY + spacing * i;

        SDL_Color color;

        if(i == selectedOption)
        {
            color = {255, 0, 0, 255}; // selecionado
        }
        else
        {
            color = {255, 255, 255, 255};
        }

        renderText(renderer, options[i].text, color, x, y);
    }
}

void Menu::moveSelection(int direction) {
    selectedOption += direction;

    if(selectedOption < 0)
    {
        selectedOption = static_cast<int>(options.size()) - 1;
    }

    if(selectedOption >= static_cast<int>(options.size()))
    {
        selectedOption = 0;
    }
}

void Menu::renderText(SDL_Renderer *renderer,
    const std::string &text,
    SDL_Color color,
    float x,
    float y) {
    SDL_Surface* surface = TTF_RenderText_Solid(
        font,
        text.c_str(),
        text.length(),
        color
    );

    if(surface == nullptr)
    {
        std::cerr << "Erro ao criar superficie do texto: "
                  << SDL_GetError()
                  << std::endl;
        return;
    }


    SDL_Texture* texture = SDL_CreateTextureFromSurface(
        renderer,
        surface
    );

    if(texture == nullptr)
    {
        std::cerr << "Erro ao criar textura do texto: "
                  << SDL_GetError()
                  << std::endl;

        SDL_DestroySurface(surface);
        return;
    }


    SDL_FRect dest;

    dest.x = x;
    dest.y = y;
    dest.w = static_cast<float>(surface->w);
    dest.h = static_cast<float>(surface->h);


    SDL_RenderTexture(
        renderer,
        texture,
        nullptr,
        &dest
    );


    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}
