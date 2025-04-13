/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Pinky
*/

#ifndef PINKY_HPP_
    #define PINKY_HPP_
    #include "Ghost.hpp"

namespace arcade::game::pacman {
    class Pinky : public Ghost {
        public:
            Pinky() = default;

            void update(types::Entity *ghost, types::Position &playerPos,
                types::Direction playerDirection);
            void enterFrightenedMode() override;
            void exitFrightenedMode() override;

        private:
            void chaseMove(types::Position &playerPos, types::Direction playerDirection);
    };
};

#endif
