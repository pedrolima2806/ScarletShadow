#include <iostream>
#include <fstream>

#include "Level.hpp"

Level::Level() : spawnPoint{0.0f, 0.0f},
                 worldWidth(0),
                 worldHeight(0)
{
}

bool Level::loadFromFile(const std::string &filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Erro ao abrir mapa: " << filePath << std::endl;
        return false;
    }

    tiles.clear();
    platforms.clear();

    std::string line;

    int row = 0;
    int maxColumns = 0;

    while (std::getline(file, line))
    {
        // Define world width
        if (static_cast<int>(line.size()) > maxColumns)
        {
            maxColumns = static_cast<int>(line.size());
        }

        for (int col = 0; col < static_cast<int>(line.size()); col++)
        {
            char symbol = line[col];

            float x = static_cast<float>(col) * TILE_SIZE;
            float y = static_cast<float>(row) * TILE_SIZE;

            switch (symbol)
            {
            case '.':
                break;

            case '#':
                tiles.emplace_back(x, y, TILE_SIZE, TileType::Solid);
                break;
            case '^':
                tiles.emplace_back(x, y, TILE_SIZE, TileType::Hazard);
                break;
            case 'S':
                spawnPoint = {x, y};
                break;
            case '=':
                platforms.emplace_back(x, y, TILE_SIZE, 10.0f);
                break;
            default:
                std::cerr << "Símbolo desconhecido em: " << row << "," << col << std::endl;
                break;
            }
        }
        ++row;
    }
    worldWidth = static_cast<float>(maxColumns) * TILE_SIZE;
    worldHeight = static_cast<float>(row) * TILE_SIZE;

    return true;
}

void Level::render(SDL_Renderer *renderer, const Camera &camera) const
{
    for (const Tile &tile : tiles)
    {
        tile.render(renderer, camera);
    }

    for (const Platform &platform : platforms)
    {
        platform.render(renderer, camera);
    }
}

const std::vector<Platform> &Level::getPlatforms() const
{
    return platforms;
}

const std::vector<Tile> &Level::getTiles() const
{
    return tiles;
}

const SDL_FPoint &Level::getSpawn() const
{
    return spawnPoint;
}

const float Level::getWorldWidth() const
{
    return worldWidth;
}

const float Level::getWorldHeight() const
{
    return worldHeight;
}
