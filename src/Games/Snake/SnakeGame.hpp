/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SnakeGame
*/

#ifndef SNAKEGAME_HPP_
    #define SNAKEGAME_HPP_
    #define MAP_WIDTH 29
    #define MAP_HEIGHT 29
    #define SNAKE_SLOWDOWN_FACTOR 6
    #include <list>
    #include <ctime>
    #include <cstdlib>
    #include "AGame.hpp"

/**
 * @file SnakeGame.hpp
 * @brief Declaration of the SnakeGame class and associated definitions.
 * @author mbarleon
 * @version 1.0
 * @date 2025-04-09
 *
 * @details
 * The SnakeGame class contains all the methods to run the snake game in the arcade.
 */
namespace arcade::game {
    /**
     * @class SnakeGame
     * @brief Class responsible for running the snake game.
     *
     * @details
     * The SnakeGame class manages the position and the growth of the snake in the game.
     * It also manages the generation of apples.
     */
    class SnakeGame : public AGame {
        public:
            SnakeGame();
            ~SnakeGame() override;

            void update(const std::pair<types::Position, types::InputEvent> event) override;
        private:
            void genApple(void);
            void addBaseEntities(void);
            void move(int offset_x, int offset_y);
            void updateDirection(const types::InputEvent event);

            int _timer = 1;
            std::size_t _size = 3;
            types::Position _apple;
            std::list<types::Position> _snake;
            types::Direction _last_move = types::RIGHT;
            types::Direction _direction = types::RIGHT;
            std::size_t _max_size = (MAP_HEIGHT - 2) * (MAP_WIDTH - 2);
    };
};

#endif /* !SNAKEGAME_HPP_ */
