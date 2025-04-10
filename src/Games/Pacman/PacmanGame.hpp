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

            void initPlayer(int y, int x);
            void initGameEntities();
            void initGameMap();
            void removeGameEntities();
            void updateWantedDirection();
            void updateDirection(types::InputEvent event);
            types::Position getNextCasePos();

            types::Direction _direction;
            types::Direction _wantedDirection;
            types::Position _pacPos;
            int _extraLifes;
            unsigned int _timer;
            static constexpr const char *_pacMap[] = {
                "XXXXXXXXXXXXXX XXXXXXXXXXXXXXX",
                "X............X X.............X",
                "X.XXXX.XXXXX.X X.XXXXXX.XXXX.X",
                "XGX  X.X   X.X X.X    X.X  XGX",
                "X.XXXX.XXXXX.XXX.XXXXXX.XXXX.X",
                "X............................X",
                "X.XXXX.XX.XXXXXXXXXX.XX.XXXX.X",
                "X.XXXX.XX.XXXX XXXXX.XX.XXXX.X",
                "X......XX....X X.....XX......X",
                "XXXXXX.XXXXX.X X.XXXXXX.XXXXXX",
                "     X.XXXXX XXX XXXXXX.X     ",
                "     X.XX         ...XX.X     ",
                "     X.XX  XX_XX XX..XX.X     ",
                "XXXXXX.XX  X   X XX..XX.XXXXXX",
                " .......   X   X XX.......... ",
                "XXXXXX.XX  XXXXX XX..XX.XXXXXX",
                "     X.XX        XX..XX.X     ",
                "     X.XX   XXX  XX..XX.X     ",
                "     X.XX XXXXXXXXX..XX.X     ",
                "XXXXXX.XX.XXXX XXXX..XX.XXXXXX",
                "X............X X.............X",
                "X.XXXX.XXXXX.X X.XXXXX..XXXX.X",
                "X.XXXX.XXXXX.XXX.XXXXX..XXXX.X",
                "XG..XX..................XX..GX",
                "XXX.XX.XX.XXXXXXXXX.XX..XX.XXX",
                "XXX.XX.XX.XXXX XXXX.XX..XX.XXX",
                "X......XX....X X....XX.......X",
                "X.XXXXXXXXXX.XXX.XXXXXXXXXXX.X",
                "X............................X",
                "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
            };
    };
};

#endif /* !PACMANGAME_HPP_ */
