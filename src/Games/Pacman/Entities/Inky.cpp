/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Inky
*/

#include "Inky.hpp"

void arcade::game::pacman::Inky::chaseMove(types::Entity *ghost,
    types::Position &playerPos, types::Position &blinkyPos,
    types::Direction playerDirection)
{
    types::Position pivot;
    types::Position target;

    switch (playerDirection) {
        case types::UP:
            pivot = {playerPos.x - 2, playerPos.y - 2};
            break;
        case types::LEFT:
            pivot = {playerPos.x - 2, playerPos.y};
            break;
        case types::RIGHT:
            pivot = {playerPos.x + 2, playerPos.y};
            break;
        default:
            pivot = {playerPos.x, playerPos.y + 2};
            break;
    }
    target = getPivotPosition(blinkyPos, pivot);
    move(getTargetDirection(target.y, target.x), ghost);
}

void arcade::game::pacman::Inky::update(types::Entity *ghost,
    types::Position &playerPos, types::Position &blinkyPos,
    types::Direction playerDirection)
{
    switch (_mode) {
        case SCATTER:
            return move(getTargetDirection(30, 29), ghost);
        case CHASE:
            return chaseMove(ghost, playerPos, blinkyPos, playerDirection);
        case FRIGHTENED:
            return moveFrightened(ghost);
        case EATEN:
            return moveEaten(ghost);
    }
}
