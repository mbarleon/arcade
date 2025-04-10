/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanMove
*/

#include "PacmanGame.hpp"

void arcade::game::PacmanGame::movePlayer(int y, int x)
{
    types::Position realPacPos = {_pacPos.x, _pacPos.y + MAP_MARGIN_TOP};
    types::Entity *pac = getEntityAt(realPacPos);

    if (pac) {
        pac->pos.x = x;
        pac->pos.y = y + MAP_MARGIN_TOP;
        _pacPos = {x, y};
    }   
}

arcade::types::Position arcade::game::PacmanGame::getNextCasePos()
{
    types::Position pos = {_pacPos.x, _pacPos.y};

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

void arcade::game::PacmanGame::updateWantedDirection()
{
    switch (_wantedDirection) {
        case types::UP:
            if (_pacMap[_pacPos.y - 1][_pacPos.x] != 'X')
                _direction = _wantedDirection;
            return;
        case types::LEFT:
            if (_pacMap[_pacPos.y][_pacPos.x - 1] != 'X')
                _direction = _wantedDirection;
            return;
        case types::RIGHT:
            if (_pacMap[_pacPos.y][_pacPos.x + 1] != 'X')
                _direction = _wantedDirection;
            return;
        default:
            if (_pacMap[_pacPos.y + 1][_pacPos.x] != 'X')
                _direction = _wantedDirection;
            return;
    }
}

void arcade::game::PacmanGame::updateDirection(types::InputEvent event)
{
    switch (event) {
        case types::AKEY_UP:
            if (_pacMap[_pacPos.y - 1][_pacPos.x] != 'X') {
                _direction = types::UP;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::UP;
            return;
        case types::AKEY_LEFT:
            if (_pacMap[_pacPos.y][_pacPos.x - 1] != 'X') {
                _direction = types::LEFT;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::LEFT;
            return;
        case types::AKEY_RIGHT:
            if (_pacMap[_pacPos.y][_pacPos.x + 1] != 'X') {
                _direction = types::RIGHT;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::RIGHT;
            return;
        case types::AKEY_DOWN:
            if (_pacMap[_pacPos.y + 1][_pacPos.x] != 'X') {
                _direction = types::DOWN;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::DOWN;
            return;
        default:
            return updateWantedDirection();
    }
}
