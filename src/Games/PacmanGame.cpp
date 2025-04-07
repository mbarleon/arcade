/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanGame
*/

#include "PacmanGame.hpp"

extern "C" {
    arcade::game::IGame *create(void)
    {
        return new arcade::game::PacmanGame();
    }

    void destroy(arcade::game::IGame *game)
    {
        delete game;
    }

    arcade::types::LibType getType(void)
    {
        return arcade::types::GAME;
    }

    const char *getName()
    {
        return "PACMAN";
    }
}

arcade::game::PacmanGame::PacmanGame()
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
        for (int x = 0; x < MAP_WIDTH; ++x)
            addEntity(getEntityType(_pacmap[y][x]), getEntityDraw(_pacmap[y][x]),
            (arcade::types::Position){x, y}, _pacmap[y][x], getEntityColor(_pacmap[y][x]).color);
}

arcade::game::PacmanGame::~PacmanGame()
{
}

void arcade::game::PacmanGame::update(const std::pair<types::Position, types::InputEvent> event)
{
}

arcade::types::EntityType arcade::game::PacmanGame::getEntityType(char c)
{
    switch (c) {
        case '0':
            return types::WALL;
        case '.':
            return types::COLLECTIBLE;
        case 'G':
            return types::FOOD;
        case '_':
            return types::OBSTACLE;
        default:
            return types::EMPTY;
    }
}

arcade::types::EntityDraw arcade::game::PacmanGame::getEntityDraw(char c)
{
    switch (c) {
        case '0':
            return types::RECTANGLE;
        case '.':
            return types::CIRCLE;
        case 'G':
            return types::CIRCLE;
        case '_':
            return types::RECTANGLE;
        default:
            return types::NONE;
    }
}

arcade::types::color_t arcade::game::PacmanGame::getEntityColor(char c)
{
    switch (c) {
        case '0':
            return {.components = {62, 78, 249, 0}};
        case '.':
            return {.components = {255, 255, 0, 0}};
        case 'G':
            return {.components = {255, 255, 0, 0}};
        case '_':
            return {.components = {62, 249, 233, 0}};
        default:
            return {.components = {0, 0, 0, 0}};
    }
}
