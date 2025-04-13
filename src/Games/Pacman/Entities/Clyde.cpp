/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Clyde
*/

#include "Clyde.hpp"

/**
 * @file Clyde.hpp
 * @brief Implements the Clyde class, which inherits directly from the ghost class.
 * @author Jason Koenig
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Implements the Clyde class, which inherits directly from the Ghost class.
 * Clyde is an orange ghost. In chase mode, he approaches the player until
 * he's within 8 squares of him, then flees and begins his cycle again.
 * In scatter mode, it moves to the bottom left corner of the maze.
 * He's the least dangerous, but can still kill the player if he's on his diagonal.
 * He starts in the cage.
 *
 * @see arcade::game::pacman::Ghost
 */

 /**
 * @brief Get ghost id.
 * @return Ghost id.
 * 
 * @see arcade::game::pacman::GameEntity
 **/
char arcade::game::pacman::Clyde::getId() const
{
    return pacman::CLYDE;
}

 /**
 * @brief Moves the ghost to a position calculated according to its mode.
 **/
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
