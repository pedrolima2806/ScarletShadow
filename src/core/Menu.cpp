#include "Menu.hpp"

#include <iostream>

#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"

Menu::Menu(TTF_Font* font, SDL_Texture* logo, SDL_Texture* backgroundTexture, SDL_Texture* markerTexture):
    selectedOption(0),
    font(font),
    logoTexture(logo),
    backgroundTexture(backgroundTexture),
    markerTexture(markerTexture),
    markerWidth(20.0f),
    markerHeight(20.0f),
    currentFrame(0),
    markerFrame(0),
    frameTimer(0.0f),
    markerFrameTimer(0.0f),
    frameDuration(0.1f),
    markerFrameDuration(0.1f),
    frameWidth(256),
    frameHeight(128),
    markerFrameWidth(16),
    markerFrameHeight(16),
    menuCycleCounter(0)
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

void Menu::renderMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
    float spacing = static_cast<float>(screenHeight) / 12.0f;

    float startX;
    float startY;

    startX = static_cast<float>(screenWidth) / 2.0f;
    startY = static_cast<float>(screenHeight) / 1.5f;

    if(backgroundTexture)
    {
        float texW;
        float texH;

        SDL_GetTextureSize(backgroundTexture, &texW, &texH);

        // escala baseada na altura da tela
        float scale = static_cast<float>(screenHeight) / texH;

        float bgWidth = texW * scale;
        float bgHeight = texH * scale;

        SDL_FRect bg;

        // centraliza horizontalmente
        bg.x = (screenWidth - bgWidth) / 2.0f;
        bg.y = 0.0f;

        bg.w = bgWidth;
        bg.h = bgHeight;

        SDL_RenderTexture(
            renderer,
            backgroundTexture,
            nullptr,
            &bg
        );
    }

    renderLogo(renderer, screenWidth, screenHeight, startX, startY);

    for(int i = 0; i < options.size(); i++)
    {
        float x = startX - getTextWidth(options[i].text) / 2.0f;
        float y = startY + spacing * i;

        SDL_Color color;

        if(i == selectedOption)
        {
            color = {255, 0, 0, 255}; //Cor quando selecionado
        }
        else
        {
            color = {255, 255, 255, 255};
        }

        renderText(renderer, options[i].text, color, x, y);

        if (i == selectedOption) {
            SDL_Color markerColor = {255, 0, 0, 255};
            renderMarker(renderer, options[i].text, color, startX, y);
            renderMarker(renderer, options[i].text, markerColor, startX, y);
        }
    }
}

void Menu::updateMenu(float deltaTime) {
    frameTimer += deltaTime;
    markerFrameTimer += deltaTime;

    if (frameTimer >= frameDuration)
    {
        frameTimer = 0.0f;

        currentFrame++;

        // Após o frame  volta para o frame 0
        if (currentFrame >= 24 && menuCycleCounter % 5 != 0)
        {
            currentFrame = 13;
            menuCycleCounter++;
        }
        if (currentFrame >= 24 && menuCycleCounter % 5 == 0)
        {
            currentFrame = 0;
            menuCycleCounter++;
        }
    }

    if (markerFrameTimer >= markerFrameDuration)
    {
        markerFrameTimer = 0.0f;
        markerFrame++;

        if (markerFrame >= 4) {
            markerFrame = 0;
        }
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

float Menu::getTextWidth(const std::string& text) {
    int width;
    int height;

    TTF_GetStringSize(font, text.c_str(), 0, &width, &height);

    return static_cast<float>(width);
}

float Menu::getTextHeight(const std::string& text) {
    int width;
    int height;

    TTF_GetStringSize(font, text.c_str(), 0, &width, &height);

    return static_cast<float>(height);
}

void Menu::renderLogo(SDL_Renderer *renderer, int screenWidth, int screenHeight, float x, float y) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_FRect src = logoAnimationLoop();

    SDL_FRect dst;
    dst.w = static_cast<float>(screenHeight) / 1.5f;
    dst.h = static_cast<float>(screenHeight) / 3.0f;
    dst.x = x - dst.w / 2.0f;
    dst.y = 0.35f * y;

    SDL_RenderTexture(renderer, logoTexture, &src, &dst);
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

void Menu::renderMarker(SDL_Renderer *renderer, const std::string& text, SDL_Color color, float x, float y)
{
    float textWidth = getTextWidth(text);
    float textHeight = getTextHeight(text);

    markerWidth = textHeight;
    markerHeight = textHeight;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_FRect leftMarker;
    leftMarker.x = x - markerWidth / 2.0f - textWidth / 2.0f - textHeight / 2.0f;
    leftMarker.y = y - textHeight * 0.05f;
    leftMarker.w = textHeight;
    leftMarker.h = textHeight;

    SDL_FRect rightMarker;
    rightMarker.x = x + textWidth / 2.0f ;
    rightMarker.y = y - textHeight * 0.05f;
    rightMarker.w = textHeight;
    rightMarker.h = textHeight;

    SDL_FRect src;
    int column = markerFrame;
    int row = 0;

    src.x = static_cast<float>(column * markerFrameWidth);
    src.y = static_cast<float>(row * markerFrameHeight);
    src.w = static_cast<float>(markerFrameWidth);
    src.h = static_cast<float>(markerFrameHeight);

    SDL_RenderTexture(renderer, markerTexture, &src, &leftMarker);
    SDL_RenderTexture(renderer, markerTexture, &src, &rightMarker);
}

SDL_FRect Menu::logoAnimationLoop() {
    SDL_FRect srcRect;

    int column = currentFrame;
    int row = 0;

    srcRect.x = static_cast<float>(column * frameWidth);
    srcRect.y = static_cast<float>(row * frameHeight);
    srcRect.w = static_cast<float>(frameWidth);
    srcRect.h = static_cast<float>(frameHeight);

    return srcRect;
}