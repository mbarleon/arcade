/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Blinky
*/

#include "Blinky.hpp"

/**
 * @file Blinky.hpp
 * @brief Implements the Blinky class, which inherits directly from the ghost class.
 * @author Jason Koenig
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Implements the Blinky class, which inherits directly from the ghost class.
 * Blinky is a red ghost. In chase mode, his target is the player. In scatter mode,
 * he joins the top-right corner of the maze. He's both the most predictable and
 * the most dangerous. He starts directly in the maze.
 *
 * @see arcade::game::pacman::Ghost
 */

 /**
 * @brief Get ghost id.
 * @return Ghost id.
 * 
 * @see arcade::game::pacman::GameEntity
 **/
char arcade::game::pacman::Blinky::getId() const
{
    return pacman::BLINKY;
}

 /**
 * @brief Moves the ghost to a position calculated according to its mode.
 **/
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
