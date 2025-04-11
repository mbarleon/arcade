/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Ghost
*/

#ifndef GHOST_HPP_
    #define GHOST_HPP_
    #include "../includes.hpp"

namespace arcade::game::pacman {
    class Ghost {
        public:
            Ghost();
            ~Ghost();

        protected:
            types::Direction getTargetDirection(int y, int x);

            void setPosition(int y, int x);
            void resetTargetMap();
            void populateTargetMapSlot(int y, int x, int sum);

        private:
            types::Direction _direction;
            types::Position _position;
            GhostMode _mode;

            int _targetMap[MAP_SIDE][MAP_SIDE];
    };
};

#endif
