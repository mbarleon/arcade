/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SnakeGame
*/

/**
 * @file SnakeGame.cpp
 * @brief Snake Game.
 * @author mbarleon
 * @version 1.0
 * @date 2025-04-09
 *
 * @details
 * This file contains the snake game.
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

/**
 * @brief Adds entities at game creation.
 * @details This function adds all the entities that are needed when the game starts.
 * @return void
 */
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

/**
 * @brief Constructor for the SnakeGame class.
 * @details This function creates all the entities needed at game start.
 * It also calls srand for all the random that will be done during the game.
 * @return void
 */
arcade::game::SnakeGame::SnakeGame()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int pos_x = static_cast<int>((MAP_HEIGHT + 1) / 2);
    int pos_y = static_cast<int>(MAP_WIDTH / 2) + 1;

    genApple();

    for (int i = static_cast<int>(-_size / 2); i < static_cast<int>(_size / 2); ++i)
        _snake.push_front(types::Position{pos_x + i, pos_y});

    addBaseEntities();
    _getScore();
}

/**
 * @brief Destructor for the SnakeGame class.
 * @details This function is empty.
 * @return void
 */
arcade::game::SnakeGame::~SnakeGame()
{
}

/**
 * @brief Change the direction of the snake.
 * @details This functions changes the direction of the snake according to the current event and the last move.
 * @return void
 */
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

/**
 * @brief Update the game.
 * @details This functions calls updateDirection, computes the movment offsets and moves the snake every SNAKE_SLOWDOWN_FACTOR frames.
 * @return void
 */
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

/**
 * @brief Generate an apple.
 * @details This functions generates an apple with random coordinates.
 * @return void
 */
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

/**
 * @brief Loads the score.
 * @details Loads the score from the file.
 * @return void
 */
void arcade::game::SnakeGame::_getScore(void)
{
    std::string line;
    std::ifstream file("Score/SnakeGame.arcade");

    if (!file || !file.is_open())
        return;
    std::getline(file, line);

    for (char& ch : line) {
        if (ch == '\n') {
            ch = '\0';
        }
    }
    try {
        std::size_t idx;
        unsigned long long val = std::stoull(line, &idx);
        if (idx != line.size())
            return;
        if (val > std::numeric_limits<std::size_t>::max())
            return;
        _high_score = static_cast<std::size_t>(val);
    } catch (const std::invalid_argument& e) {
        file.close();
        return;
    } catch (const std::out_of_range& e) {
        file.close();
        return;
    }
    file.close();
}

/**
 * @brief Saves the score.
 * @details Saves the score to the file.
 * @return void
 */
void arcade::game::SnakeGame::_saveScore(void)
{
    std::ofstream file("Score/SnakeGame.arcade");

    if (!file || !file.is_open())
        return;
    _high_score = _high_score < _size - SNAKE_BASE_SIZE || _high_score > _max_size ? _size - SNAKE_BASE_SIZE : _high_score;
    file << _high_score << std::endl;
}

/**
 * @brief Adds the scores.
 * @details Adds the scores to the screen.
 * @return void
 */
void arcade::game::SnakeGame::add_scores(void)
{
    std::string high;
    std::string score = "Score: " + std::to_string(_size - SNAKE_BASE_SIZE);
    removeEntityAt(types::Position{0, 0});
    addEntity(types::EMPTY, types::TEXT, types::Position{0, 0}, ' ', getRGBA(255, 255, 255, 255).color, score);


    if (_high_score <= _max_size) {
        high = "High Score: " + std::to_string(_high_score);
    } else {
        high = "High Score: cheater";
    }
    removeEntityAt(types::Position{30 - static_cast<int>(high.size()), 0});
    _high_score = _high_score < _size - SNAKE_BASE_SIZE ? _size - SNAKE_BASE_SIZE : _high_score;
    if (_high_score <= _max_size) {
        high = "High Score: " + std::to_string(_high_score);
    } else {
        high = "High Score: cheater";
    }
    addEntity(types::EMPTY, types::TEXT, types::Position{30 - static_cast<int>(high.size()), 0}, ' ', getRGBA(255, 255, 255, 255).color, high);
}

/**
 * @brief Move the snake.
 * @details This functions moves the snake and removes the useless entities.
 * It sets _gameOver to true if needed.
 * @return void
 */
void arcade::game::SnakeGame::move(int offset_x, int offset_y)
{
    types::Position snake_front = _snake.front();
    types::Position front = types::Position{snake_front.x + offset_x, snake_front.y + offset_y};
    types::Entity *frontEntity = getEntityAt(front);
    add_scores();

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
        if (_size == _max_size) {
            _saveScore();
            _gameOver = true;
        }
        removeEntityAt(_apple);
        genApple();
        addEntity(types::FOOD, types::CIRCLE, _apple, 'o', getRGBA(255, 0, 0, 255).color, "");
    } else {
        _saveScore();
        _gameOver = true;
    }
}
