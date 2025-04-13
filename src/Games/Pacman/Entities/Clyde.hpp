/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Clyde
*/

/**
 * @file Clyde.hpp
 * @brief Contains the behavior of the ghost Clyde.
 * @author Jason KOENIG
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Contains the update method, which defines the behavior of the Clyde ghost.
 *
 * @see arcade::game::pacman::Ghost
 */
#ifndef CLYDE_HPP_
    #define CLYDE_HPP_
    #include "Ghost.hpp"

namespace arcade::game::pacman {
    /**
     * @class Clyde
     * @brief Implements the Clyde class, which inherits directly from the ghost class.
     *
     * @see arcade::game::pacman::Ghost
     */
    class Clyde : public Ghost {
        public:
            Clyde() = default;

            char getId() const override;
            void update(types::Entity *ghost, types::Position &playerPos);
    };
};

#endif
