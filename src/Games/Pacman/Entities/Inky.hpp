/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Inky
*/

/**
 * @file Inky.hpp
 * @brief Contains the behavior of the ghost Inky.
 * @author Jason KOENIG
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Contains the update method, which defines the behavior of the Inky ghost.
 *
 * @see arcade::game::pacman::Ghost
 */
#ifndef INKY_HPP_
    #define INKY_HPP_
    #include "Ghost.hpp"

namespace arcade::game::pacman {
    /**
     * @class Inky
     * @brief Implements the Inky class, which inherits directly from the ghost class.
     *
     * @see arcade::game::pacman::Ghost
     */
    class Inky : public Ghost {
        public:
            Inky() = default;

            char getId() const override;
            void update(types::Entity *ghost, types::Position &playerPos,
                types::Position &blinkyPos, types::Direction playerDirection);

        private:
            void chaseMove(types::Position &playerPos, types::Position &blinkyPos,
                types::Direction playerDirection);
    };
};

#endif
