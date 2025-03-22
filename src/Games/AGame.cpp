/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** AGame.cpp
*/

#include "AGame.hpp"

/*
 * push an entity at position (specify the char c for lib-Ncurses / non-GUI)
 *  - EntityType the type of the entity (obstracle, food...)
 *  - EntityDraw what should the API draw (rectangle, circle...)
 *  - Position vector2u where the entity should be displayed
 *  - char for TTY-API (like ncurses)
 *  - uint32_t is the color of the entity
 */
void arcade::game::AGame::addEntity(types::EntityType type, types::EntityDraw draw, types::Position pos, char c,
    uint32_t color)
{
    types::Entity entity = {.type = type, .pos = pos, .display_char = c, .color = color};

    _entities.insert({draw, entity});
}

/*
 * INFO:
 * remove entity at position {x, y}
 */
void arcade::game::AGame::removeEntityAt(const types::Position &pos)
{
    for (auto it = _entities.begin(); it != _entities.end(); ++it) {
        if (it->second.pos == pos) {
            _entities.erase(it);
            break;
        }
    }
}

/*
 * INFO:
 * get entity at position {x, y}
 */
arcade::types::Entity *arcade::game::AGame::getEntityAt(const types::Position &pos)
{
    for (auto it = _entities.begin(); it != _entities.end(); ++it) {
        if (it->second.pos == pos) {
            return &it->second;
        }
    }
    return nullptr;
}

const std::string &arcade::game::AGame::getName() const
{
    return _name;
}

int arcade::game::AGame::getScore() const
{
    return _score;
}

bool arcade::game::AGame::isGameOver() const
{
    return _gameOver;
}

const std::unordered_map<arcade::types::EntityDraw, arcade::types::Entity> &arcade::game::AGame::getEntities() const
{
    return _entities;
}

const std::pair<uint32_t, uint32_t> &arcade::game::AGame::getMapSize() const
{
    return _mapSize;
}

void arcade::game::AGame::setGameOver(bool gameOver)
{
    _gameOver = gameOver;
}

void arcade::game::AGame::clearEntities()
{
    _entities.clear();
}

/*
 * INFO:
 * this is where you initialize game attributes
 */
void arcade::game::AGame::init()
{
    _score = 0;
    _gameOver = 0;
    clearEntities();
}

/*
 * INFO:
 * game receive graphical API events. InputEvent is defined `Types.hpp`
 */
void arcade::game::AGame::handleInput(__attribute__((unused)) const std::vector<types::InputEvent> event)
{
    //
}

void arcade::game::AGame::update()
{
    //
}

/*
 * INFO:
 * this is where you destroy game attributes
 */
void arcade::game::AGame::stop()
{
    //
}
