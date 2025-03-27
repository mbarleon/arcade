/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Core
*/

#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include "../Games/IGame.hpp"
#include "../Graphicals/IDisplayModule.hpp"

#define GAME_CREATE arcade::game::IGame *(*)()
#define DISPLAY_CREATE arcade::display::IDisplayModule *(*)()

#define SELECTED_CAST const std::string (*)()
#define TYPE_CAST types::LibType (*)(void)

#define GAME_DESTROY void (*)(arcade::game::IGame *game)
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

        private:
            void load_game(const char *game);
            void load_display(const char *display);
            std::string getPath(std::filesystem::path);
            const char *nextLib(const std::string &libName);
            void runSingleGame(std::string &game, const char *display);

            bool _quit = false;

            game::IGame *_game = nullptr;
            display::IDisplayModule *_display = nullptr;

            void *_game_handle = NULL;
            void *_display_handle = NULL;

            std::unordered_map<std::string, std::string> _games;
            std::unordered_map<std::string, std::string> _displays;

            const std::unordered_map<std::string, std::string> _libs = {
                {"lib/arcade_ndk++.so", "NDK"},
                {"lib/arcade_aalib.so", "AALIB"},
                {"lib/arcade_libcaca.so", "LIBCACA"},
                {"lib/arcade_allegro5.so", "ALLEGRO"},
                {"lib/arcade_xlib.so", "XLIB"},
                {"lib/arcade_gtk+.so", "GTK"},
                {"lib/arcade_sfml.so", "SFML"},
                {"lib/arcade_irrlicht.so", "IRRLICHT"},
                {"lib/arcade_opengl.so", "OPENGL"},
                {"lib/arcade_vulkan.so", "VULKAN"},
                {"lib/arcade_qt5.so", "QT"},
                {"lib/arcade_snake.so", "SNAKE"},
                {"lib/arcade_minesweeper.so", "MINESWEEPER"},
                {"lib/arcade_nibbler.so", "NIBBLER"},
                {"lib/arcade_pacman.so", "PACMAN"},
                {"lib/arcade_qix.so", "QIX"},
                {"lib/arcade_centipede.so", "CENTIPEDE"},
                {"lib/arcade_solarfox.so", "SOLARFOX"}
            };
    };
};
