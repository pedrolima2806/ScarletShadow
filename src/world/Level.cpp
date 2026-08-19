#include <iostream>
#include <fstream>

#include "Level.hpp"

Level::Level():
    spawnPoint{0.0f, 0.0f}
{
    tiles.emplace_back(
       100.0f,
       280.0f,
       TILE_SIZE,
       TileType::Solid
   );

    tiles.emplace_back(
        140.0f,
        280.0f,
        TILE_SIZE,
        TileType::Hazard
    );

    tiles.emplace_back(
        180.0f,
        280.0f,
        TILE_SIZE,
        TileType::Solid
    );

    platforms.emplace_back(
        0.0f,
        470.0f,
        1280.0f,
        20.0f
    );

    platforms.emplace_back(
        100.0f,
        400.0f,
        250.0f,
        20.0f
    );

    platforms.emplace_back(
        300.0f,
        340.0f,
        200.0f,
        20.0f
    );
}

bool Level::loadFromFile(const std::string &filePath) {
    std::ifstream file(filePath);

    if (!file.is_open())
    {std::cerr << "Erro ao abrir mapa: " << filePath << std::endl;
        return false;
    }

    tiles.clear();
    platforms.clear();

    std::string line;

    int row = 0;
    while (std::getline(file, line)) {
        for (int col = 0; col < static_cast<int>(line.size()); col++) {
            char symbol = line[col];

            float x = static_cast<float>(col) * TILE_SIZE;
            float y = static_cast<float>(row) * TILE_SIZE;

            switch (symbol) {
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

    return true;
}

void Level::render(SDL_Renderer *renderer) const {
    for (const Tile& tile : tiles) {
        tile.render(renderer);
    }

    for (const Platform &platform : platforms) {
        platform.render(renderer);
    }
}

const std::vector<Platform> &Level::getPlatforms() const {
    return platforms;
}

const std::vector<Tile> &Level::getTiles() const {
    return tiles;
}

const SDL_FPoint& Level::getSpawn() const {
    return spawnPoint;
}


