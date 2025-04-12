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
            types::Sprite getEntitySprite(char c);
            types::Position getPosition(int y, int x);
            int getFoodValue(char food);

            void initGameEntities();
            void initGameMap();
            void removeGameEntities();
            void updateGhosts(types::Position &playerPos);

            void saveHighScore();
            void loadHighScore();
            void refreshScore();

            pacman::Player player;

            types::Position _ghostsTargetPos[4];

            int _highScore;
            int _dotCpt;
            size_t _timer;
    };
};

#endif
