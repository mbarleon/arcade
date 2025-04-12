/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Clyde
*/

#include "Clyde.hpp"

void arcade::game::pacman::Clyde::chaseMove(types::Entity *ghost,
    types::Position &playerPos)
{
    if (getDistance(_position, playerPos) >= 8)
        move(getTargetDirection(playerPos.y, playerPos.x), ghost);
    else
        move(getTargetDirection(30, 0), ghost);
}

void arcade::game::pacman::Clyde::update(types::Entity *ghost,
    types::Position &playerPos)
{
    switch (_mode) {
        case SCATTER:
            return move(getTargetDirection(30, 0), ghost);
        case CHASE:
            return chaseMove(ghost, playerPos);
        case FRIGHTENED:
            return moveFrightened(ghost);
        case EATEN:
            return moveEaten(ghost);
    }
}
