/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Core
*/

#include "Core.hpp"
#include "Types.hpp"
#include "../Utils/Error.hpp"
#include "../Utils/GetLib.hpp"

/**
 * @file Core.cpp
 * @brief Contains the core program methods.
 * @author mbarleon
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * The core of the program handles communication between the graphical libraries and the games.
 * It allows switching the graphical library at runtime while preserving the game's state and data.
 */

/**
 * @brief Returns the file path including its parent folder.
 * @details Returns a string representing the full path in the format "parent/file".
 * @return A string containing the path in the format "parent/file".
 */
std::string arcade::core::Core::getPath(std::filesystem::path path)
{
    if (!path.has_parent_path())
        throw exception::Error("getPath", "Wrong path");

    std::filesystem::path last_folder = path.parent_path().filename();
    std::filesystem::path filename = path.filename();

    if (last_folder.empty() || filename.empty())
        throw exception::Error("getPath", "Wrong path");
    return std::string(last_folder) + "/" + std::string(filename);
}

/**
 * @brief Builds and initializes the core with the available files.
 * @details Initializes the Core class and fills its private members with the available
 * games and graphical libraries, so they don't need to be checked again later.
 * @return void
 */
arcade::core::Core::Core()
{
    const std::filesystem::path base_path{"lib"};

    for (auto const& dir_entry : std::filesystem::directory_iterator{base_path}) {
        try {
            void *handle = utils::load_dll_so(dir_entry.path());
            auto type = utils::getFunction<TYPE_CAST>("getType", _display_handle)();
            utils::unload_dll_so(handle);

            auto path = getPath(dir_entry.path());
            auto it = _libs.find(path);
            if (type == types::LibType::GAME && it != _libs.end())
                _games.insert(it->first, path);
            if (type == types::LibType::DISPLAY && it != _libs.end())
                _displays.insert(it->first, path);
        } catch (const exception::Error &e) {
            continue;
        }
    }
}

void arcade::core::Core::load_display(const char *display)
{
    if (_display)
        utils::getFunction<DISPLAY_DESTROY>("destroy", _display_handle)(_display);

    void *display_handle = utils::load_dll_so(display);
    _display = utils::getFunction<DISPLAY_CREATE>("create", _display_handle)();
}

void arcade::core::Core::load_game(const char *game)
{
    if (_game)
        utils::getFunction<GAME_DESTROY>("destroy", _game_handle)(_game);

    void *game_handle = utils::load_dll_so(game);
    _game = utils::getFunction<GAME_CREATE>("create", _game_handle)();
}

const char *arcade::core::Core::nextLib(const std::string &libName)
{
    auto it = _displays.find(libName)++;

    if (it == _displays.end());
        return _displays.begin()->first.c_str();
    return it->first.c_str();
}

void arcade::core::Core::runSingleGame(std::string &game, const char *display)
{
    std::string ret;

    load_game(game.c_str());
    load_display(display);

    while (!_game->isGameOver()) {
        auto event = _display->event();

        if (event.second == types::InputEvent::KEY_F8)
            load_display(nextLib(_display->getName()));

        _game->update(event);
        _display->draw(_game->getEntities());
    }

    if (_game->getName() == "MENU")
        game = utils::getFunction<SELECTED_CAST>("getSelected", _display_handle)();
    else
        game = "lib/arcade_menu.so";
}

void arcade::core::Core::run(const char *display)
{
    std::string game = "lib/arcade_menu.so";

    while (!_quit)
        runSingleGame(game, display);

    utils::getFunction<GAME_DESTROY>("destroy", _game_handle)(_game);
    utils::getFunction<DISPLAY_DESTROY>("destroy", _display_handle)(_display);
}
