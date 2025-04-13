/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Ghost
*/

/**
 * @file Ghost.hpp
 * @brief Contains the behavior of the ghosts.
 * @author Jason KOENIG
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Contains all the methods that allow ghosts to move around the maze
 * and switch modes to attack the player in different ways, or to give him respite.
 *
 * @see arcade::game::PacmanGame
 */

#ifndef GHOST_HPP_
    #define GHOST_HPP_
    #include "../includes.hpp"
    #include <cmath>

namespace arcade::game::pacman {
    /**
     * @class Ghost
     * @brief Abstract base class for ghosts in the Pacman game.
     * @details Contains the basic methods inherited by ghosts, enabling
     * them to move and perform actions in the maze.
     *
     * @see arcade::game::PacmanGame
     */
    class Ghost {
        public:
            Ghost();
            ~Ghost();

            types::Position &getPosition();
            GhostMode getMode() const;
            size_t getTimer() const;
            virtual char getId() const = 0;

            void move(types::Direction target, types::Entity *ghost);

            void setTimer(size_t timer);
            void setMode(GhostMode mode);
            void loadLastMode();
            void setPosition(int y, int x);
            void setDirection(types::Direction direction);

        protected:
            types::Direction getTargetDirection(int y, int x);
            types::Position getPivotPosition(types::Position &src,
                types::Position &pivot);
            int getDistance(types::Position &pos, types::Position &pos2);

            void reverseDirection();
            void moveFrightened(types::Entity *ghost);
            void moveEaten(types::Entity *ghost);

            types::Direction _direction;
            types::Position _position;
            GhostMode _mode;
            GhostMode _lastMode;

        private:
            types::Direction getTargetDirectionCorrected(int y, int x);
            void resetTargetMap();
            void populateTargetMapSlot(int y, int x, int sum);
            types::Direction getRandomDirection();

            int _targetMap[MAP_SIDE][MAP_SIDE];
            size_t _timer;
    };
};

#endif
