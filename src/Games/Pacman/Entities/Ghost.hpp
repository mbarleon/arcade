/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Ghost
*/

#ifndef GHOST_HPP_
    #define GHOST_HPP_
    #include "../includes.hpp"
    #include <cmath>

namespace arcade::game::pacman {
    class Ghost {
        public:
            Ghost();
            ~Ghost();

            void move(types::Direction target, types::Entity *ghost);

            void setMode(GhostMode mode);

        protected:
            types::Direction getTargetDirection(int y, int x);
            types::Position getPivotPosition(types::Position &src,
                types::Position &pivot);
            int getDistance(types::Position &pos, types::Position &pos2);

            void setPosition(int y, int x);
            void reverseDirection();

            void moveFrightened(types::Entity *ghost);
            void moveEaten(types::Entity *ghost);

            types::Direction _direction;
            types::Position _position;
            GhostMode _mode;

        private:
            types::Direction getTargetDirectionCorrected(int y, int x);
            void resetTargetMap();
            void populateTargetMapSlot(int y, int x, int sum);
            types::Direction getRandomDirection();

            int _targetMap[MAP_SIDE][MAP_SIDE];
    };
};

#endif
