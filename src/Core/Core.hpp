/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Core
*/

#pragma once

#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <cstring>
#include <filesystem>
#include <unordered_map>
#include "../Games/IGame.hpp"
#include "../Graphicals/IDisplayModule.hpp"

#define THREAD_SLEEP 16
#define STRING_CAST const char *(*)()
#define TYPE_CAST types::LibType (*)(void)
#define GAME_CREATE arcade::game::IGame *(*)()
#define GAME_DESTROY void (*)(arcade::game::IGame *game)
#define DISPLAY_CREATE arcade::display::IDisplayModule *(*)()
#define DISPLAY_DESTROY void (*)(arcade::display::IDisplayModule *display)

/**
 * @file Core.hpp
 * @brief Declaration of the Core class and associated definitions.
 * @author mbarleon
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * The Core class launches the program and acts as a bridge between graphical libraries and games.
 * It also handles dynamic switching between libraries or games at runtime.
 *
 * In addition, it manages communication between these two key components and handles file-related
 * errors during program startup.
 */

namespace arcade::core {
    /**
     * @class Core
     * @brief Main class responsible for communication between games and graphical libraries.
     *
     * @details
     * The Core class manages the main loop of the Arcade program.
     * It handles dynamic loading, management, and runtime switching of games and graphical libraries.
     * It also centralizes event handling, rendering, and error management during startup or execution.
     */
    class Core {
        public:
            Core();
            ~Core() = default;

            void run(const char *display);

            std::unordered_map<std::string, std::string> getGames(void) const;
            std::unordered_map<std::string, std::string> getDisplays(void) const;

        private:
            const char *nextLib(void);
            void loadGame(const char *game);
            void loadDisplay(const char *display);
            std::string getPath(std::filesystem::path);
            void runSingleGame(std::string &game, std::string &display);
            int handleInputs(const std::string &game, const std::pair<types::Position, types::InputEvent> &event);

            bool _quit = false;

            game::IGame *_game = nullptr;
            display::IDisplayModule *_display = nullptr;

            void *_gameHandle = nullptr;
            void *_displayHandle = nullptr;

            const char *_libName;
            const char *_gameName;

            std::unordered_map<std::string, std::string> _games;
            std::unordered_map<std::string, std::string> _displays;
    };
};
