/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Clyde
*/

#include "Clyde.hpp"

void arcade::game::pacman::Clyde::enterFrightenedMode()
{
}

void arcade::game::pacman::Clyde::exitFrightenedMode()
{
}

void arcade::game::pacman::Clyde::update(types::Entity *ghost,
    types::Position &playerPos)
{
    switch (_mode) {
        case SCATTER:
            _direction = getTargetDirection(28, 1);
            break;
        case CHASE:
            _direction = (getDistance(_position, playerPos) >= 8) ?
            getTargetDirection(playerPos.y, playerPos.x) : getTargetDirection(28, 1);
            break;
        case FRIGHTENED:
            return moveFrightened(ghost);
        case EATEN:
            return moveEaten(ghost);
    }
    move(_direction, ghost);
}
