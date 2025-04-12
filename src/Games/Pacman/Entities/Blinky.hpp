/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Blinky
*/

#ifndef BLINKY_HPP_
    #define BLINKY_HPP_
    #include "Ghost.hpp"

namespace arcade::game::pacman {
    class Blinky : public Ghost {
        public:
            Blinky() = default;

            void update(types::Entity *ghost, types::Position &playerPos);
    };
};

#endif
