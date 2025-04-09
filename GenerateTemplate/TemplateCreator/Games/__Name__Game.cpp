/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** __Name__Game
*/

#include "__Name__Game.hpp"

extern "C" {
    arcade::game::IGame *create(void)
    {
        return new arcade::game::__Name__Game();
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
        return "__NAME__";
    }
}

arcade::game::__Name__Game::__Name__Game()
{

}

arcade::game::__Name__Game::~__Name__Game()
{

}

void arcade::game::__Name__Game::update(const std::pair<types::Position, types::InputEvent> event)
{

}
