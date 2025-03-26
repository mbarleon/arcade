/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** AGame.cpp
*/

#include "AGame.hpp"
#include <algorithm>

/*
 * public
 */

arcade::game::AGame::~AGame()
{
    /* empty dtor */
}

/*
 * create/remove/get Entity
 */

/*
 * push an entity at position (specify the char c for lib-Ncurses / non-GUI)
 *  - EntityType the type of the entity (obstracle, food...)
 *  - EntityDraw what should the API draw (rectangle, circle...)
 *  - Position vector2u where the entity should be displayed
 *  - char for TTY-API (like ncurses)
 *  - uint32_t is the color of the entity
 *
 * using an entityIndex for faster lookups
 */
void arcade::game::AGame::addEntity(types::EntityType type, types::EntityDraw draw, types::Position pos, char c,
    uint32_t color)
{
    types::Entity entity = {.type = type, .pos = pos, .display_char = c, .color = color};

    _entities[draw].push_back(entity);
    _entityIndex[pos] = &_entities[draw].back();
}

/*
 * remove entity at position {x, y}
 */
void arcade::game::AGame::removeEntityAt(const types::Position &pos)
{
    const auto it = _entityIndex.find(pos);

    if (it != _entityIndex.end()) {
        for (auto &[draw, entity_vec] : _entities) {
            const auto entity_it = std::find_if(entity_vec.begin(), entity_vec.end(),
                [&](const types::Entity &e) { return &e == it->second; });

            if (entity_it != entity_vec.end()) {
                entity_vec.erase(entity_it);
                break;
            }
        }
        _entityIndex.erase(it);
    }
}

/*
 * get entity at position {x, y}
 */
arcade::types::Entity *arcade::game::AGame::getEntityAt(const types::Position &pos)
{
    const auto it = _entityIndex.find(pos);

    return (it != _entityIndex.end()) ? it->second : nullptr;
}

/*
 * getters
 */

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

const arcade::game::AGame::Entities &arcade::game::AGame::getEntities() const
{
    return _entities;
}

/*
 * setters
 */
void arcade::game::AGame::setGameOver(bool gameOver)
{
    _gameOver = gameOver;
}

void arcade::game::AGame::clearEntities()
{
    _entities.clear();
}

/*
 * must be implemented in inheritance
 */

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
void arcade::game::AGame::update(__attribute__((unused)) const std::vector<types::InputEvent> events)
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
