/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SnakeGame
*/

#include "SnakeGame.hpp"

extern "C" {
    arcade::game::IGame *create(void)
    {
        return new arcade::game::SnakeGame();
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
        return "SNAKE";
    }
}

arcade::game::SnakeGame::SnakeGame()
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
        for (int x = 0; x < MAP_WIDTH; ++x)
            if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
                addEntity(types::WALL, types::RECTANGLE,
                    (arcade::types::Position){x, y}, 'x',
                    getRGBA(255, 255, 0, 255).color, "");
}

arcade::game::SnakeGame::~SnakeGame()
{
}

void arcade::game::SnakeGame::update(const std::pair<types::Position, types::InputEvent> event)
{
    (void)event;
}
