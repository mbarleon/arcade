/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanGame
*/

#ifndef PACMANGAME_HPP_
    #define PACMANGAME_HPP_
    #define MAP_HEIGHT 31
    #define MAP_WIDTH 28
    #include "../AGame.hpp"

namespace arcade::game {
    class PacmanGame : public AGame {
        public:
            PacmanGame();
            ~PacmanGame() override;

            void update(const std::pair<types::Position, types::InputEvent> event) override;

        private:
            arcade::types::EntityType getEntityType(char c);
            arcade::types::EntityDraw getEntityDraw(char c);
            arcade::types::color_t getEntityColor(char c);

            static constexpr const char *_pacmap[] = {
                "0000000000000000000000000000",
                "0............00............0",
                "0.0000.00000.00.00000.0000.0",
                "0G0000.00000.00.00000.0000G0",
                "0.0000.00000.00.00000.0000.0",
                "0..........................0",
                "0.0000.00.00000000.00.0000.0",
                "0.0000.00.00000000.00.0000.0",
                "0......00....00....00......0",
                "000000.00000 00 00000.000000",
                "     0.00000 00 00000.0     ",
                "     0.00          00.0     ",
                "     0.00 000__000 00.0     ",
                "000000.00 0      0 00.000000",
                "      .   0      0   .      ",
                "000000.00 0      0 00.000000",
                "     0.00 00000000 00.0     ",
                "     0.00          00.0     ",
                "     0.00 00000000 00.0     ",
                "000000.00 00000000 00.000000",
                "0............00............0",
                "0.0000.00000.00.00000.0000.0",
                "0.0000.00000.00.00000.0000.0",
                "0G..00................00..G0",
                "000.00.00.00000000.00.00.000",
                "000.00.00.00000000.00.00.000",
                "0......00....00....00......0",
                "0.0000000000.00.0000000000.0",
                "0.0000000000.00.0000000000.0",
                "0..........................0",
                "0000000000000000000000000000"
            };
    };    
};

#endif /* !PACMANGAME_HPP_ */
