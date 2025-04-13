/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Pinky
*/

/**
 * @file Pinky.hpp
 * @brief Contains the behavior of the ghost Pinky.
 * @author Jason KOENIG
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Contains the update method, which defines the behavior of the Pinky ghost.
 *
 * @see arcade::game::pacman::Ghost
 */
#ifndef PINKY_HPP_
    #define PINKY_HPP_
    #include "Ghost.hpp"

namespace arcade::game::pacman {
    /**
     * @class Pinky
     * @brief Implements the Pinky class, which inherits directly from the ghost class.
     *
     * @see arcade::game::pacman::Ghost
     */
    class Pinky : public Ghost {
        public:
            Pinky() = default;

            char getId() const override;
            void update(types::Entity *ghost, types::Position &playerPos,
                types::Direction playerDirection);

        private:
            void chaseMove(types::Position &playerPos, types::Direction playerDirection);
    };
};

#endif
