/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SnakeGame
*/

#ifndef SNAKEGAME_HPP_
    #define SNAKEGAME_HPP_
    #define MAP_WIDTH 30
    #define MAP_HEIGHT 30
    #include "AGame.hpp"

namespace arcade::game {
    class SnakeGame : public AGame {
        public:
            SnakeGame();
            ~SnakeGame() override;

            void update(const std::pair<types::Position, types::InputEvent> event) override;
    };
};

#endif /* !SNAKEGAME_HPP_ */
