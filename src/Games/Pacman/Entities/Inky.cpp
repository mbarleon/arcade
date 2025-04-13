/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Inky
*/

#include "Inky.hpp"

/**
 * @file Inky.hpp
 * @brief Implements the Inky class, which inherits directly from the ghost class.
 * @author Jason Koenig
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Implements the Inky class, which inherits directly from the Ghost class.
 * Inky is a green ghost (cyan in the original game). In chase mode,
 * it moves to the position obtained by mirroring Blinky's position relative
 * to the player's +2 position (in the player's direction), which acts as a pivot.
 * In scatter mode, it moves to the lower right-hand corner of the maze. He's the
 * most unpredictable. He starts in the cage.
 *
 * @see arcade::game::pacman::Ghost
 */

/**
 * @brief Get ghost id.
 * @return Ghost id.
 * 
 * @see arcade::game::pacman::GameEntity
 **/
char arcade::game::pacman::Inky::getId() const
{
    return pacman::INKY;
}

/**
 * @brief Set Inky's direction in chase mode.
 * @param playerPos Player's position in the maze.
 * @param blinkyPos Blinky's position in the maze.
 * @param playerDirection Player's direction.
 * 
 * @see arcade::game::pacman::Inky::getPivotPosition
 * @see arcade::game::pacman::Inky::getTargetDirection
 */
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

 /**
 * @brief Moves the ghost to a position calculated according to its mode.
 **/
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
