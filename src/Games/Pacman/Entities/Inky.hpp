/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Inky
*/

#ifndef INKY_HPP_
    #define INKY_HPP_
    #include "Ghost.hpp"

namespace arcade::game::pacman {
    class Inky : public Ghost {
        public:
            Inky() = default;

            void update(types::Entity *ghost, types::Position &playerPos,
                types::Position &blinkyPos, types::Direction playerDirection);

        private:
            void chaseMove(types::Entity *ghost, types::Position &playerPos,
                types::Position &blinkyPos, types::Direction playerDirection);
    };
};

#endif
