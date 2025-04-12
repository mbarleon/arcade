/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Pinky
*/

#include "Pinky.hpp"

void arcade::game::pacman::Pinky::update(types::Entity *ghost)
{
    switch (_mode) {
        case SCATTER:
            return move(getTargetDirection(-3, 2), ghost);
        case CHASE:
            return;
        case FRIGHTENED:
            return moveFrightened(ghost);
        case EATEN:
            return moveEaten(ghost);
    }
}
