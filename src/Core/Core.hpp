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

            void run(const char *game);

        private:
            void event();
            /* TODO */
            void update();
            /* TODO */
            void draw();

            using CreateGame = game::IGame *(*) ();
            using DestroyGame = void (*)(game::IGame *);

            using CreateDisplay = display::IDisplayModule *(*) ();
            using DestroyDisplay = void (*)(display::IDisplayModule *);

            std::unique_ptr<game::IGame> _game;
            std::unique_ptr<display::IDisplayModule> _display;
    };
};
