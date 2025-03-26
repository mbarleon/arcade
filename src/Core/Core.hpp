/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Core.hpp
*/

#pragma once

#include "../Games/IGame.hpp"
#include "../Graphicals/IDisplayModule.hpp"
#include <memory>

namespace arcade::core {
    class Core {
        public:
            static constexpr char *displays[] = {
                "arcade_ndk++.so", "arcade_aalib.so", "arcade_libcaca.so",
                "arcade_allegro5.so", "arcade_xlib.so", "arcade_gtk+.so",
                "arcade_sfml.so", "arcade_irrlicht.so", "arcade_opengl.so",
                "arcade_vulcan.so", "arcade_qt5.so"
            };

            static constexpr char *games[] = {
                "arcade_snake.so", "arcade_minesweeper.so", "arcade_nibbler.so",
                "arcade_pacman.so", "arcade_qix.so", "arcade_centipede.so",
                "arcade_solarfox.so", "arcade_menu.so"
            };

            Core();
            ~Core();

            /* entry point to call in main */
            void run(const char *display);

        private:
            /* TODO */
            void update();
            /* TODO */
            void draw();

            /* function pointer to fetch create() entry point in the Game */
            using CreateGame = game::IGame *(*) ();
            /* function pointer to fetch destroy() entry point in the Game */
            using DestroyGame = void (*)(game::IGame *);

            /* function pointer to fetch create() entry point in the Display/Display */
            using CreateDisplay = display::IDisplayModule *(*) ();
            /* function pointer to fetch destroy() entry point in the Display/Display */
            using DestroyDisplay = void (*)(display::IDisplayModule *);

            std::unique_ptr<game::IGame> _game;
            std::unique_ptr<game::IGame> _menu;
            std::unique_ptr<display::IDisplayModule> _display;
    };
};
