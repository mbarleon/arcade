/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_
    #include "../includes.hpp"

namespace arcade::game::pacman {
    class Player {
        public:
            Player();
            ~Player();

            types::Position getNextPos();
            types::Position &getPos();
            types::Position getRealPos();
            types::Direction getDirection() const;
            int getExtraLifes() const;
            int getKillRow() const;

            void setDirection(types::Direction direction);
            void setPosition(int y, int x);
            void setExtraLifes(int extraLifes);
            void setKillRow(int killRow);
            void updateWantedDirection();
            void updateDirection(types::InputEvent event);
            void move(int y, int x, types::Entity *player);

        private:
            types::Direction _direction;
            types::Direction _wantedDirection;
            types::Position _position;

            int _extraLifes;
            int _killRow;
    };
};

#endif
