/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Ghost
*/

#include "Ghost.hpp"

arcade::game::pacman::Ghost::Ghost() : _direction(types::UP),
    _position({0, 0}), _mode(SCATTER)
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

void arcade::game::pacman::Ghost::reverseDirection()
{
    switch (_direction) {
        case types::UP:
            _direction = types::DOWN;
            break;
        case types::LEFT:
            _direction = types::RIGHT;
            break;
        case types::RIGHT:
            _direction = types::LEFT;
            break;
        default:
            _direction = types::UP;
            break;
    }
}

void arcade::game::pacman::Ghost::setMode(GhostMode mode)
{
    if (_mode == FRIGHTENED)
        reverseDirection();
    _mode = mode;
}

void arcade::game::pacman::Ghost::resetTargetMap()
{
    for (int y = 0; y < MAP_SIDE; ++y)
        for (int x = 0; x < MAP_SIDE; ++x)
            _targetMap[y][x] = -1;
}

arcade::types::Direction arcade::game::pacman::Ghost::getRandomDirection()
{
    bool directions[4] = {true, true, true, true};
    int possibleDirections = 0;
    int nextDirection;

    if ((_position.y == 11 || _position.y == 23) &&
    (_position.x >= 12 && _position.x <= 17)) {
        if (_direction == types::LEFT)
            return types::LEFT;
        if (_direction == types::RIGHT)
            return types::RIGHT;
    }
    switch (_direction) {
        case types::DOWN:
            directions[types::UP] = false;
            break;
        case types::LEFT:
            directions[types::RIGHT] = false;
            break;
        case types::RIGHT:
            directions[types::LEFT] = false;
            break;
        default:
            directions[types::DOWN] = false;
            break;
    }
    if (pacMap[_position.y - 1][_position.x] == WALL ||
    pacMap[_position.y - 1][_position.x] == DOOR)
        directions[types::UP] = false;
    if (_position.y != 14 && _position.x != 0 &&
    (pacMap[_position.y][_position.x - 1] == WALL ||
    pacMap[_position.y][_position.x - 1] == DOOR))
        directions[types::LEFT] = false;
    if (_position.y != 14 && _position.x != 27 &&
    (pacMap[_position.y][_position.x + 1] == WALL ||
    pacMap[_position.y][_position.x + 1] == DOOR))
        directions[types::RIGHT] = false;
    if (pacMap[_position.y + 1][_position.x] == WALL ||
    pacMap[_position.y + 1][_position.x] == DOOR)
        directions[types::DOWN] = false;
    for (int i = 0; i < 4; ++i)
        if (directions[i])
            ++possibleDirections;
    nextDirection = rand() % possibleDirections;
    for (; nextDirection < 4; ++nextDirection)
        if (directions[nextDirection])
            return static_cast<types::Direction>(nextDirection);
    return types::UP;
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

arcade::types::Direction arcade::game::pacman::Ghost::getTargetDirectionCorrected(int y, int x)
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

arcade::types::Direction arcade::game::pacman::Ghost::getTargetDirection(int y, int x)
{
    if (x < 0)
        x = 0;
    if (x > 29)
        x = 29;
    if (y < 0)
        y = 0;
    if (y > 29)
        y = 29;
    if ((_position.x >= 12 && _position.x <= 14) &&
    (_position.y >= 12 && _position.y <= 14)) {
        y = 11;
        x = 13;
    }
    if ((_position.y == 11 || _position.y == 23) &&
    (_position.x >= 12 && _position.x <= 17)) {
        if (_direction == types::LEFT)
            return types::LEFT;
        if (_direction == types::RIGHT)
            return types::RIGHT;
    }
    return getTargetDirectionCorrected(y, x);
}

void arcade::game::pacman::Ghost::move(types::Direction target, types::Entity *ghost)
{
    types::Position nextPos;

    switch (target) {
        case types::UP:
            nextPos = {_position.x, _position.y - 1};
            break;
        case types::LEFT:
            nextPos = {_position.x - 1, _position.y};
            break;
        case types::RIGHT:
            nextPos = {_position.x + 1, _position.y};
            break;
        default:
            nextPos = {_position.x, _position.y + 1};
            break;
    }
    if (nextPos.x == -1)
        nextPos.x = 29;
    else if (nextPos.x == 30)
        nextPos.x = 0;
    ghost->pos.x = nextPos.x;
    ghost->pos.y = nextPos.y + MAP_MARGIN_TOP;
    _position = {nextPos.x, nextPos.y};
}

void arcade::game::pacman::Ghost::moveFrightened(types::Entity *ghost)
{
    move(getRandomDirection(), ghost);
}

void arcade::game::pacman::Ghost::moveEaten(types::Entity *ghost)
{
    move(getTargetDirection(13, 13), ghost);
}
