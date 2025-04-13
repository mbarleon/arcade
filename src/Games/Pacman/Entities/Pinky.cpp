/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Pinky
*/

#include "Pinky.hpp"
/**
 * @file Pinky.hpp
 * @brief Implements the Pinky class, which inherits directly from the ghost class.
 * @author Jason Koenig
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Implements the Pinky class, which inherits directly from the Ghost class.
 * Pinky is a pink ghost. In chase mode, it moves to the player's +4 position
 * (in the player's direction). In scatter mode, she moves to the upper left
 * of the maze. She starts in the cage, but exits directly at the start of the game.
 *
 * @see arcade::game::pacman::Ghost
 */

 /**
 * @brief Get ghost id.
 * @return Ghost id.
 * 
 * @see arcade::game::pacman::GameEntity
 **/
char arcade::game::pacman::Pinky::getId() const
{
    return pacman::PINKY;
}

/**
 * @brief Set Pinky's direction in chase mode.
 * @param playerPos Player's position in the maze.
 * @param playerDirection Player's direction.
 * 
 * @see arcade::game::pacman::Inky::getTargetDirection
 */
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

 /**
 * @brief Moves the ghost to a position calculated according to its mode.
 **/
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
