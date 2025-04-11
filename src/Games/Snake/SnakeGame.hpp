/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SnakeGame
*/

#ifndef SNAKEGAME_HPP_
    #define SNAKEGAME_HPP_
    #define MAP_WIDTH 30
    #define MAP_HEIGHT 29
    #define SNAKE_BASE_SIZE 4
    #define SNAKE_SLOWDOWN_FACTOR 6
    #include <list>
    #include <ctime>
    #include <cstdlib>
    #include <fstream>
    #include <limits>
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

    class SnakeGame : public AGame {
        public:
            SnakeGame();
            ~SnakeGame() override;

            void update(const std::pair<types::Position, types::InputEvent> event) override;
        private:
            void genApple(void);
            void _getScore(void);
            void add_scores(void);
            void _saveScore(void);
            void addBaseEntities(void);
            void move(int offset_x, int offset_y);
            void updateDirection(const types::InputEvent event);

            int _timer = 1;
            types::Position _apple;
            std::size_t _high_score = 0;
            std::list<types::Position> _snake;
            std::size_t _size = SNAKE_BASE_SIZE;
            types::Direction _last_move = types::RIGHT;
            types::Direction _direction = types::RIGHT;
            std::size_t _max_size = (MAP_HEIGHT - 2) * (MAP_WIDTH - 2);
    };
};

#endif /* !SNAKEGAME_HPP_ */
