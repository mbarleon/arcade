/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** AGame
*/

#include "AGame.hpp"

arcade::game::AGame::AGame()
{
    _score = 0;
    _gameOver = false;
    clearEntities();
}

void arcade::game::AGame::update(const std::pair<types::Position, types::InputEvent>)
{
}

const arcade::game::IGame::Entities &arcade::game::AGame::getEntities() const
{
    return _entities;
}

int arcade::game::AGame::getScore() const
{
    return _score;
}

bool arcade::game::AGame::isGameOver() const
{
    return _gameOver;
}

void arcade::game::AGame::setGameOver(bool state)
{
    _gameOver = state;
}

void arcade::game::AGame::addEntity(types::EntityType type, types::EntityDraw draw,
    types::Position pos, char c, uint32_t color, const std::string str, const types::Sprite sprite)
{
    types::Entity entity = {.type = type, .pos = pos, .display_char = c,
        .color = color, .str = str, .sprite = sprite};

    _entities[draw].push_back(entity);
    _entitiesIndex[pos] = &_entities[draw].back();
}

void arcade::game::AGame::removeEntityAt(const types::Position &pos)
{
    const auto it = _entitiesIndex.find(pos);

    if (it != _entitiesIndex.end()) {
        for (auto &[draw, vect] : _entities) {
            for (auto vect_it = vect.begin(); vect_it != vect.end(); ++vect_it) {
                if (&(*vect_it) == it->second) {
                    vect.erase(vect_it);
                    _entitiesIndex.erase(it);
                    return;
                }
            }
        }
        _entitiesIndex.erase(it);
    }
}

arcade::types::Entity *arcade::game::AGame::getEntityAt(const types::Position &pos)
{
    const auto it = _entitiesIndex.find(pos);

    if (it != _entitiesIndex.end())
        return it->second;
    return nullptr;
}

void arcade::game::AGame::clearEntities()
{
    _entities.clear();
}

arcade::types::color_t arcade::game::AGame::getRGBA(int r, int g, int b, int a)
{
    types::color_t color;

    color.components[types::R] = r;
    color.components[types::G] = g;
    color.components[types::B] = b;
    color.components[types::A] = a;
    return color;
}
