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

void arcade::game::SnakeGame::addBaseEntities(void)
{
    for (int y = 2; y < MAP_HEIGHT + 2; ++y)
        for (int x = 0; x < MAP_WIDTH; ++x)
            if (x == 0 || x == MAP_WIDTH - 1 || y == 2 || y == MAP_HEIGHT + 1)
                addEntity(types::WALL, types::RECTANGLE,
                    (types::Position){x, y}, '#',
                    getRGBA(0, 0, 255, 255).color, "");

    addEntity(types::FOOD, types::CIRCLE, _apple, 'o', getRGBA(255, 0, 0, 255).color, "");

    for (auto it = _snake.begin(); it != _snake.end(); ++it) {
        addEntity(types::PLAYER, types::RECTANGLE,
            types::Position{it->x, it->y}, 'x',
            getRGBA(0, 255, 0, 255).color, "");
    }
}

arcade::game::SnakeGame::SnakeGame()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int pos_x = static_cast<int>((MAP_HEIGHT + 1) / 2) + 2;
    int pos_y = static_cast<int>((MAP_WIDTH + 1) / 2);

    genApple();

    _snake.push_front(types::Position{pos_x - 1, pos_y});
    _snake.push_front(types::Position{pos_x, pos_y});
    _snake.push_front(types::Position{pos_x + 1, pos_y});

    addBaseEntities();
}

arcade::game::SnakeGame::~SnakeGame()
{
}

void arcade::game::SnakeGame::updateDirection(const types::InputEvent event)
{
    switch (event) {
        case types::AKEY_UP:
            if (_last_move != types::DOWN)
                _direction = types::UP;
            return;
        case types::AKEY_DOWN:
            if (_last_move != types::UP)
                _direction = types::DOWN;
            return;
        case types::AKEY_LEFT:
            if (_last_move != types::RIGHT)
                _direction = types::LEFT;
            return;
        case types::AKEY_RIGHT:
            if (_last_move != types::LEFT)
                _direction = types::RIGHT;
            return;
        default:
            return;
    }
}

void arcade::game::SnakeGame::update(const std::pair<types::Position, types::InputEvent> event)
{
    if (_gameOver)
        return;

    updateDirection(event.second);

    int offset_x = 0;
    int offset_y = 0;
    switch (_direction) {
        case types::RIGHT:
            offset_x = 1;
            break;
        case types::LEFT:
            offset_x = -1;
            break;
        case types::UP:
            offset_y = -1;
            break;
        case types::DOWN:
            offset_y = 1;
            break;
        default:
            break;
    }

    _timer = (_timer + 1) % SNAKE_SLOWDOWN_FACTOR;
    if (_timer == 0)
        move(offset_x, offset_y);
}

void arcade::game::SnakeGame::genApple(void)
{
    int min = 1;
    int max_h = MAP_HEIGHT + 1;
    int max_w = MAP_WIDTH - 1;

    int random_h = min + 2 + std::rand() % (max_h - (min + 2));
    int random_w = min + std::rand() % (max_w - min);

    for (int y = random_h; y < max_h; ++y) {
        for (int x = random_w; x < max_w; ++x) {
            if (getEntityAt(types::Position{x, y}) == nullptr) {
                _apple = types::Position{x, y};
                return;
            }
        }
    }
    for (int y = min + 2; y < random_h; ++y) {
        for (int x = min; x < max_w; ++x) {
            if (getEntityAt(types::Position{x, y}) == nullptr) {
                _apple = types::Position{x, y};
                return;
            }
        }
    }
}

void arcade::game::SnakeGame::move(int offset_x, int offset_y)
{
    types::Position snake_front = _snake.front();
    types::Position front = types::Position{snake_front.x + offset_x, snake_front.y + offset_y};
    types::Entity *frontEntity = getEntityAt(front);

    std::string str = "Score: " + std::to_string(_size - 3);

    removeEntityAt(types::Position{0, 0});
    addEntity(types::EMPTY, types::TEXT, types::Position{0, 0}, ' ', getRGBA(0, 255, 255, 255).color, str);

    _last_move = _direction;
    if (frontEntity == nullptr) {
        _snake.push_front(front);
        addEntity(types::PLAYER, types::RECTANGLE, front, 'x',
            getRGBA(0, 255, 0, 255).color, "");
        removeEntityAt(_snake.back());
        _snake.pop_back();
    } else if (front == _apple) {
        _snake.push_front(front);
        addEntity(types::PLAYER, types::RECTANGLE, front, 'x',
            getRGBA(0, 255, 0, 255).color, "");
        _size++;
        if (_size == _max_size)
            _gameOver = true;
        removeEntityAt(_apple);
        genApple();
        addEntity(types::FOOD, types::CIRCLE, _apple, 'o', getRGBA(255, 0, 0, 255).color, "");
    } else {
        _gameOver = true;
    }
}
