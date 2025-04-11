/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanGame
*/

#ifndef PACMANGAME_HPP_
    #define PACMANGAME_HPP_
    #define MAP_SIDE 30
    #define MAP_MARGIN_TOP 6
    #include "../AGame.hpp"
    #include <cstring>
    #include <fstream>

namespace arcade::game {
    class PacmanGame : public AGame {
        public:
            enum GameEntity {
                PAC = 'O',
                BLINKY = 'B',
                INKY = 'I',
                PINKY = 'P',
                CLYDE = 'C',
                GUM = '.',
                GUM2 = 'G',
                WALL = '#',
                DOOR = '_',
                APPLE = 'a',
                BANANA = 'b',
                CHERRIES = 'c',
                PINEAPPLE = 'p',
                POTION = 'u',
                KEY = 'k'
            };

            using GameEvent = const std::pair<types::Position, types::InputEvent>;

            PacmanGame();
            ~PacmanGame() override;

            void update(GameEvent event) override;

        private:
            types::EntityType getEntityType(char c);
            types::EntityDraw getEntityDraw(char c);
            types::Sprite getEntitySprite(char c);
            types::Position getPosition(int y, int x);
            types::Position getNextCasePos();
            int getFoodValue(char food);
            types::Direction populateTargetMap(types::Direction ghostDirection,
                types::Position &mapGhostPos, types::Position &mapTargetPos);
            void populateTargetMapPos(int y, int x, int sum);
            void loadHighScore();

            void initGameEntities();
            void initGameMap();
            void initGameTargetMap();
            void saveHighScore();
            void removeGameEntities();

            void movePlayer(int y, int x);
            void updateWantedDirection();
            void updateDirection(types::InputEvent event);
            void refreshScore();

            types::Direction _direction;
            types::Direction _wantedDirection;
            types::Position _pacPos;
            types::Position _ghostsTargetPos[4];

            int _extraLifes;
            int _ghostKillRow;
            int _highScore;
            unsigned int _timer;

            int _targetMap[MAP_SIDE][MAP_SIDE];
            static constexpr const char *_pacMap[] = {
                "############## ###############",
                "#............# #.............#",
                "#.####.#####.# #.######.####.#",
                "#G#  #.#   #.# #.#    #.#  #G#",
                "#.####.#####.###.######.####.#",
                "#............................#",
                "#.####.##.##########.##.####.#",
                "#.####.##.#### #####.##.####.#",
                "#......##....# #.....##......#",
                "######.#####.# #.######.######",
                "     #.##### ### ######.#     ",
                "     #.##         ...##.#     ",
                "     #.##  ##_## ##..##.#     ",
                "######.##  #   # ##..##.######",
                " .......   #   # ##.......... ",
                "######.##  ##### ##..##.######",
                "     #.##        ##..##.#     ",
                "     #.##   ###  ##..##.#     ",
                "     #.## #########..##.#     ",
                "######.##.#### ####..##.######",
                "#............# #.............#",
                "#.####.#####.# #.#####..####.#",
                "#.####.#####.###.#####..####.#",
                "#G..##..................##..G#",
                "###.##.##.#########.##..##.###",
                "###.##.##.#### ####.##..##.###",
                "#......##....# #....##.......#",
                "#.##########.###.###########.#",
                "#............................#",
                "##############################"
            };
    };
};

#endif
