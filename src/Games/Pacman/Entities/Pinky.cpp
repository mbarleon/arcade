/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Pinky
*/

#include "Pinky.hpp"

void arcade::game::pacman::Pinky::chaseMove(types::Entity *ghost,
    types::Position &playerPos, types::Direction playerDirection)
{
    switch (playerDirection) {
        case types::UP:
            return move(getTargetDirection(playerPos.y - 4, playerPos.x - 4), ghost);
        case types::LEFT:
            return move(getTargetDirection(playerPos.y, playerPos.x - 4), ghost);
        case types::RIGHT:
            return move(getTargetDirection(playerPos.y, playerPos.x + 4), ghost);
        default:
            return move(getTargetDirection(playerPos.y + 4, playerPos.x), ghost);
    }
}

void arcade::game::pacman::Pinky::update(types::Entity *ghost,
    types::Position &playerPos, types::Direction playerDirection)
{
    switch (_mode) {
        case SCATTER:
            return move(getTargetDirection(-3, 2), ghost);
        case CHASE:
            return chaseMove(ghost, playerPos, playerDirection);
        case FRIGHTENED:
            return moveFrightened(ghost);
        case EATEN:
            return moveEaten(ghost);
    }
}
