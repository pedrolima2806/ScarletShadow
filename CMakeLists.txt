cmake_minimum_required(VERSION 3.20)

project(SombraEscarlate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================
# Bibliotecas vendored
# ============================================================

add_subdirectory(vendor/SDL)
add_subdirectory(vendor/SDL_image)
add_subdirectory(vendor/SDL_mixer)
add_subdirectory(vendor/SDL_ttf)

# ============================================================
# Executável
# ============================================================

add_executable(SombraEscarlate
        src/main.cpp
        src/core/Game.cpp
        src/core/Game.hpp
        src/core/Game.hpp
        src/entities/Player.cpp
        src/entities/Player.hpp
        src/entities/Platform.cpp
        src/entities/Platform.hpp
        src/world/Level.cpp
        src/world/Level.hpp
        src/world/Tile.cpp
        src/world/Tile.hpp
)

# ============================================================
# Includes
# ============================================================

target_include_directories(SombraEscarlate PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor

)

# ============================================================
# Bibliotecas
# ============================================================

target_link_libraries(SombraEscarlate PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_mixer::SDL3_mixer
        SDL3_ttf::SDL3_ttf
)