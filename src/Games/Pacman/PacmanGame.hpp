/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanGame
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

            void initGameEntities();
            void initGameMap();
            void removeGameEntities();
            void updateGhosts();

            void saveHighScore();
            void loadHighScore();
            void refreshScore();

            pacman::Player _player;
            pacman::Blinky _blinky;
            pacman::Pinky _pinky;
            pacman::Inky _inky;
            pacman::Clyde _clyde;

            int _highScore;
            int _dotCpt;
            int _level;
            size_t _timer;
    };
};

#endif
