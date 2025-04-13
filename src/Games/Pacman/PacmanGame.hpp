/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanGame
*/

/**
 * @file PacmanGame.hpp
 * @brief Main file of the Pacman game.
 * @author Jason KOENIG
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Contains the entire game and directly manages mechanics that require
 * global access, such as texture changes or collisions.
 *
 * @see arcade::game::AGame
 */

#ifndef PACMANGAME_HPP_
    #define PACMANGAME_HPP_
    #include "../AGame.hpp"
    #include "includes.hpp"
    #include "Entities/Player.hpp"
    #include "Entities/Blinky.hpp"
    #include "Entities/Pinky.hpp"
    #include "Entities/Inky.hpp"
    #include "Entities/Clyde.hpp"
    #include <cstring>
    #include <fstream>

namespace arcade::game {
    /**
     * @class PacmanGame
     * @brief Main class of the Pacman game.
     * @details Manages the entire game using the AGame inheritance and
     * handles events sent by the Core. Manages various timers such as the fruit
     * disappearance time or the duration of ghost states. The time gets
     * shorter as the player levels up.
     *
     * @see arcade::game::AGame
     */
    class PacmanGame : public AGame {
        public:
            using GameEvent = const std::pair<types::Position, types::InputEvent>;

            PacmanGame();
            ~PacmanGame() override;

            void update(GameEvent event) override;

        private:
            types::EntityType getEntityType(char c);
            types::EntityDraw getEntityDraw(char c);
            types::color_t getEntityColor(char c);
            types::Sprite getEntitySprite(char c);
            types::Position getPosition(int y, int x);
            int getFoodValue(char food);
            types::Entity *getEntityAtByChar(char c);
            int getCycleTime();

            void initGameEntities();
            void initGameMap();
            void removeEntityAtByChar(char c);
            void resetGameEntities();
            bool updateGhost(pacman::Ghost &ghost, types::Position &playerPos);
            void updateGhosts();
            void generateFood();
            void exitGhostSpecialModes(pacman::Ghost &ghost);
            void setGhostsFrightened();
            void setGhostSkin(char c, char skin);
            void restoreGhostSkin(char c);

            void saveHighScore();
            void loadHighScore();
            void refreshScore();

            pacman::Player _player;
            pacman::Blinky _blinky;
            pacman::Pinky _pinky;
            pacman::Inky _inky;
            pacman::Clyde _clyde;

            types::Position _playerStartPos;
            int _highScore;
            int _dotCpt;
            int _remainingDots;
            int _level;
            size_t _timer;
            size_t _fruitTimer;
    };
};

#endif
