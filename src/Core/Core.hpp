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
            Core();
            ~Core();

            /* entry point to call in main */
            void run(const char *game);

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
            std::unique_ptr<display::IDisplayModule> _display;
    };
};
