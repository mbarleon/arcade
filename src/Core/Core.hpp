/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Core
*/

#pragma once

#include <string>
#include <memory>
#include "../Games/IGame.hpp"
#include "../Graphicals/IDisplayModule.hpp"

#define GAME_CREATE arcade::game::IGame *(*)()
#define DISPLAY_CREATE arcade::display::IDisplayModule *(*)()

#define SELECTED_CAST const std::string (*)()

#define GAME_DESTROY void (*)(arcade::game::IGame *game)
#define DISPLAY_DESTROY void (*)(arcade::display::IDisplayModule *display)

namespace arcade::core {
    class Core {
        public:
            Core() = default;
            ~Core() = default;

            void run(const char *display);

        private:
            void load_game(const char *game);
            void load_display(const char *display);
            void runSingleGame(std::string &game, const char *display);

            bool _quit = false;

            game::IGame *_game = nullptr;
            display::IDisplayModule *_display = nullptr;

            void *_game_handle = NULL;
            void *_display_handle = NULL;
    };
};
