/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Blinky
*/

#include "Blinky.hpp"

char arcade::game::pacman::Blinky::getId() const
{
    return pacman::BLINKY;
}

void arcade::game::pacman::Blinky::update(types::Entity *ghost,
    types::Position &playerPos)
{
    switch (_mode) {
        case SCATTER:
            _direction = getTargetDirection(1, 28);
            break;
        case CHASE:
            _direction = getTargetDirection(playerPos.y, playerPos.x);
            break;
        case FRIGHTENED:
            return moveFrightened(ghost);
        case EATEN:
            return moveEaten(ghost);
    }
    move(_direction, ghost);
}
