/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Clyde
*/

#ifndef CLYDE_HPP_
    #define CLYDE_HPP_
    #include "Ghost.hpp"

namespace arcade::game::pacman {
    class Clyde : public Ghost {
        public:
            Clyde() = default;

            void update(types::Entity *ghost, types::Position &playerPos);

        private:
            void chaseMove(types::Entity *ghost, types::Position &playerPos);
    };
};

#endif
