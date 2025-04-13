/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Pinky
*/

#include "Pinky.hpp"

char arcade::game::pacman::Pinky::getId() const
{
    return pacman::PINKY;
}

void arcade::game::pacman::Pinky::chaseMove(types::Position &playerPos,
    types::Direction playerDirection)
{
    switch (playerDirection) {
        case types::UP:
            _direction = getTargetDirection(playerPos.y - 4, playerPos.x - 4);
            return;
        case types::LEFT:
            _direction = getTargetDirection(playerPos.y, playerPos.x - 4);
            return;
        case types::RIGHT:
            _direction = getTargetDirection(playerPos.y, playerPos.x + 4);
            return;
        default:
            _direction = getTargetDirection(playerPos.y + 4, playerPos.x);
            return;
    }
}

void arcade::game::pacman::Pinky::update(types::Entity *ghost,
    types::Position &playerPos, types::Direction playerDirection)
{
    switch (_mode) {
        case SCATTER:
            _direction = getTargetDirection(1, 1);
            break;
        case CHASE:
            chaseMove(playerPos, playerDirection);
            break;
        case FRIGHTENED:
            return moveFrightened(ghost);
        case EATEN:
            return moveEaten(ghost);
    }
    move(_direction, ghost);
}
