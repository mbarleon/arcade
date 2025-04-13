/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Inky
*/

#include "Inky.hpp"

void arcade::game::pacman::Inky::enterFrightenedMode()
{
}

void arcade::game::pacman::Inky::exitFrightenedMode()
{
}

void arcade::game::pacman::Inky::chaseMove(types::Position &playerPos,
    types::Position &blinkyPos, types::Direction playerDirection)
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
    _direction = getTargetDirection(target.y, target.x);
}

void arcade::game::pacman::Inky::update(types::Entity *ghost,
    types::Position &playerPos, types::Position &blinkyPos,
    types::Direction playerDirection)
{
    switch (_mode) {
        case SCATTER:
            _direction = getTargetDirection(28, 28);
            break;
        case CHASE:
            chaseMove(playerPos, blinkyPos, playerDirection);
            break;
        case FRIGHTENED:
            return moveFrightened(ghost);
        case EATEN:
            return moveEaten(ghost);
    }
    move(_direction, ghost);
}
