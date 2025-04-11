/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Player
*/

#include "Player.hpp"

arcade::game::pacman::Player::Player() : _direction(types::LEFT),
    _wantedDirection(types::LEFT), _position({0, 0}),
    _extraLifes(2), _killRow(0)
{
}

arcade::game::pacman::Player::~Player()
{
}

arcade::types::Position arcade::game::pacman::Player::getNextPos()
{
    types::Position pos = {_position.x, _position.y};

    switch (_direction) {
        case types::UP:
            --pos.y;
            break;
        case types::LEFT:
            --pos.x;
            break;
        case types::RIGHT:
            ++pos.x;
            break;
        default:
            ++pos.y;
            break;
    }
    return pos;
}

arcade::types::Position &arcade::game::pacman::Player::getPos()
{
    return _position;
}

arcade::types::Position arcade::game::pacman::Player::getRealPos()
{
    return {_position.x, _position.y + MAP_MARGIN_TOP};
}

int arcade::game::pacman::Player::getExtraLifes() const
{
    return _extraLifes;
}

int arcade::game::pacman::Player::getKillRow() const
{
    return _killRow;
}

void arcade::game::pacman::Player::setPosition(int y, int x)
{
    _position.x = x;
    _position.y = y;
}

void arcade::game::pacman::Player::setExtraLifes(int extraLifes)
{
    _extraLifes = extraLifes;
}

void arcade::game::pacman::Player::setKillRow(int killRow)
{
    _killRow = killRow;
}

void arcade::game::pacman::Player::updateWantedDirection()
{
    switch (_wantedDirection) {
        case types::UP:
            if (pacMap[_position.y - 1][_position.x] != WALL &&
            pacMap[_position.y - 1][_position.x] != DOOR)
                _direction = _wantedDirection;
            return;
        case types::LEFT:
            if (pacMap[_position.y][_position.x - 1] != WALL &&
            pacMap[_position.y][_position.x - 1] != DOOR)
                _direction = _wantedDirection;
            return;
        case types::RIGHT:
            if (pacMap[_position.y][_position.x + 1] != WALL &&
            pacMap[_position.y][_position.x + 1] != DOOR)
                _direction = _wantedDirection;
            return;
        default:
            if (pacMap[_position.y + 1][_position.x] != WALL &&
            pacMap[_position.y + 1][_position.x] != DOOR)
                _direction = _wantedDirection;
            return;
    }
}

void arcade::game::pacman::Player::updateDirection(types::InputEvent event)
{
    switch (event) {
        case types::AKEY_UP:
            if (pacMap[_position.y - 1][_position.x] != WALL &&
            pacMap[_position.y - 1][_position.x] != DOOR) {
                _direction = types::UP;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::UP;
            return;
        case types::AKEY_LEFT:
            if (pacMap[_position.y][_position.x - 1] != WALL &&
            pacMap[_position.y][_position.x - 1] != DOOR) {
                _direction = types::LEFT;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::LEFT;
            return;
        case types::AKEY_RIGHT:
            if (pacMap[_position.y][_position.x + 1] != WALL &&
            pacMap[_position.y][_position.x + 1] != DOOR) {
                _direction = types::RIGHT;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::RIGHT;
            return;
        case types::AKEY_DOWN:
            if (pacMap[_position.y + 1][_position.x] != WALL &&
            pacMap[_position.y + 1][_position.x] != DOOR) {
                _direction = types::DOWN;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::DOWN;
            return;
        default:
            return updateWantedDirection();
    }
}

void arcade::game::pacman::Player::move(int y, int x, types::Entity *player)
{
    if (x == -1)
        x = 29;
    else if (x == 30)
        x = 0;
    player->pos.x = x;
    player->pos.y = y + MAP_MARGIN_TOP;
    _position = {x, y};   
}
