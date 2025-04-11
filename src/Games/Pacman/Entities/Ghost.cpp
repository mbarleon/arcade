/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Ghost
*/

#include "Ghost.hpp"

arcade::game::pacman::Ghost::Ghost() : _direction(types::UP), _position({0, 0})
{
}

arcade::game::pacman::Ghost::~Ghost()
{
}

void arcade::game::pacman::Ghost::setPosition(int y, int x)
{
    _position.x = x;
    _position.y = y;
}

void arcade::game::pacman::Ghost::resetTargetMap()
{
    for (int y = 0; y < MAP_SIDE; ++y)
        for (int x = 0; x < MAP_SIDE; ++x)
            _targetMap[y][x] = -1;
}

void arcade::game::pacman::Ghost::populateTargetMapSlot(int y, int x, int sum)
{
    if (y == 14) {
        if (x == -1)
            x = 29;
        if (x == 30)
            x = 0;
    }
    if (y < 0 || x < 0 || y > 29 || x > 29 ||
    pacMap[y][x] == WALL || pacMap[y][x] == CLYDE ||
    pacMap[y][x] == BLINKY || pacMap[y][x] == INKY ||
    pacMap[y][x] == PINKY)
        return;
    if (_targetMap[y][x] == -1 || sum < _targetMap[y][x]) {
        _targetMap[y][x] = sum;
        populateTargetMapSlot(y - 1, x, sum + 1);
        populateTargetMapSlot(y + 1, x, sum + 1);
        populateTargetMapSlot(y, x + 1, sum + 1);
        populateTargetMapSlot(y, x - 1, sum + 1);
    }
}

arcade::types::Direction arcade::game::pacman::Ghost::getTargetDirection(int y, int x)
{
    int directions[4];

    resetTargetMap();
    _targetMap[_position.y][_position.x] = -2;
    _targetMap[y][x] = 0;

    populateTargetMapSlot(y - 1, x, 1);
    populateTargetMapSlot(y + 1, x, 1);
    populateTargetMapSlot(y, x + 1, 1);
    populateTargetMapSlot(y, x - 1, 1);

    if (y == 14) {
        switch (x) {
            case 0:
                directions[types::LEFT] = _targetMap[_position.y][29];
                directions[types::RIGHT] = _targetMap[_position.y][_position.x + 1];
                break;
            case 29:
                directions[types::LEFT] = _targetMap[_position.y][_position.x - 1];
                directions[types::RIGHT] = _targetMap[_position.y][0];
                break;
            default:
                directions[types::LEFT] = _targetMap[_position.y][_position.x - 1];
                directions[types::RIGHT] = _targetMap[_position.y][_position.x + 1];
                break;
        }
    }
    directions[types::UP] = _targetMap[_position.y - 1][_position.x];
    directions[types::DOWN] = _targetMap[_position.y + 1][_position.x];

    if (directions[types::RIGHT] != -1 &&
    (directions[types::RIGHT] < directions[types::DOWN] || directions[types::DOWN] == -1) &&
    (directions[types::RIGHT] < directions[types::LEFT] || directions[types::LEFT] == -1) &&
    (directions[types::RIGHT] < directions[types::UP] || directions[types::UP] == -1) &&
    _direction != types::LEFT)
        return types::RIGHT;
    if (directions[types::DOWN] != -1 &&
    (directions[types::DOWN] < directions[types::RIGHT] || directions[types::RIGHT] == -1) &&
    (directions[types::DOWN] < directions[types::LEFT] || directions[types::LEFT] == -1) &&
    (directions[types::DOWN] < directions[types::UP] || directions[types::UP] == -1) &&
    _direction != types::UP)
        return types::DOWN;
    if (directions[types::LEFT] != -1 &&
    (directions[types::LEFT] < directions[types::RIGHT] || directions[types::RIGHT] == -1) &&
    (directions[types::LEFT] < directions[types::DOWN] || directions[types::DOWN] == -1) &&
    (directions[types::LEFT] < directions[types::UP] || directions[types::UP] == -1) &&
    _direction != types::RIGHT)
        return types::LEFT;
    return types::UP;
}
