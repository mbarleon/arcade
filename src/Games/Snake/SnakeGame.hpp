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
    #define SNAKE_SLOWDOWN_FACTOR 1
    #include <list>
    #include <ctime>
    #include <cstdlib>
    #include "AGame.hpp"

namespace arcade::game {
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

            int _timer = 0;
            std::size_t _size = 3;
            types::Position _apple;
            std::list<types::Position> _snake;
            types::Direction _last_move = types::RIGHT;
            types::Direction _direction = types::RIGHT;
            std::size_t _max_size = (MAP_HEIGHT - 2) * (MAP_WIDTH - 2);
    };
};

#endif /* !SNAKEGAME_HPP_ */
