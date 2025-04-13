/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Blinky
*/

#ifndef BLINKY_HPP_
    #define BLINKY_HPP_
    #include "Ghost.hpp"

/**
 * @file Blinky.hpp
 * @brief Contains the behavior of the ghost Blinky.
 * @author Jason KOENIG
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Contains the update method, which defines the behavior of the Blinky ghost.
 *
 * @see arcade::game::pacman::Ghost
 */
namespace arcade::game::pacman {
    /**
     * @class Blinky
     * @brief Implements the Blinky class, which inherits directly from the ghost class.
     *
     * @see arcade::game::pacman::Ghost
     */
    class Blinky : public Ghost {
        public:
            Blinky() = default;

            char getId() const override;
            void update(types::Entity *ghost, types::Position &playerPos);
    };
};

#endif
