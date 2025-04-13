/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Core
*/

#include "Core.hpp"
#include "../../include/Types.hpp"
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
            auto type = utils::getFunction<TYPE_CAST>("getType", handle)();
            std::string name(utils::getFunction<STRING_CAST>("getName", handle)());
            utils::unload_dll_so(handle);

            auto path = getPath(dir_entry.path());
            if (type == types::LibType::GAME || type == types::LibType::MENU)
                _games.insert({name, path});
            if (type == types::LibType::DISPLAY)
                _displays.insert({name, path});
        } catch (const exception::Error &e) {
            continue;
        }
    }
}

/**
 * @brief Dynamically loads and unloads graphical libraries.
 * @details If a graphical library is already loaded, it is first unloaded
 * before loading the new one.
 * @return void
 */
void arcade::core::Core::loadDisplay(const char *display)
{
    if (_display != nullptr) {
        utils::getFunction<DISPLAY_DESTROY>("destroy", _displayHandle)(_display.release());
        utils::unload_dll_so(_displayHandle);
    }

    _displayHandle = utils::load_dll_so(display);
    if (utils::getFunction<TYPE_CAST>("getType", _displayHandle)() != types::DISPLAY) {
        utils::unload_dll_so(_displayHandle);
        throw exception::Error("loadDisplay", "Not a display");
    }
    _libName = utils::getFunction<STRING_CAST>("getName", _displayHandle)();
    _display.reset(utils::getFunction<DISPLAY_CREATE>("create", _displayHandle)());
}

/**
 * @brief Dynamically loads a game.
 * @details If a game is already loaded, it is first unloaded before loading the new one.
 * @return void
 */
void arcade::core::Core::loadGame(const char *game)
{
    if (_game != nullptr) {
        utils::getFunction<GAME_DESTROY>("destroy", _gameHandle)(_game.release());
        utils::unload_dll_so(_gameHandle);
    }

    _gameHandle = utils::load_dll_so(game);
    auto type = utils::getFunction<TYPE_CAST>("getType", _gameHandle)();
    if (type != types::GAME && type != types::MENU) {
        utils::unload_dll_so(_gameHandle);
        throw exception::Error("loadGame", "Not a game");
    }
    _gameName = utils::getFunction<STRING_CAST>("getName", _gameHandle)();
    _game.reset(utils::getFunction<GAME_CREATE>("create", _gameHandle)());
}

/**
 * @brief Switches to the next graphical library.
 * @details Switches from the currently loaded graphical library to the next one
 * in the list of libraries stored in the Core (private variable).
 * @return The file path of the selected graphical library.
 */
const char *arcade::core::Core::nextLib(void)
{
    auto it = _displays.find(_libName);

    it++;
    if (it == _displays.end())
        return _displays.begin()->second.c_str();
    return it->second.c_str();
}

/**
 * @brief Handle special inputs in the core.
 * @details Allows the user to change library, quit or restart game.
 * @return An int that tells the caller loop if it should break or not.
 */
int arcade::core::Core::handleInputs(const std::string &game, std::string &display,
    const std::pair<types::Position, types::InputEvent> &event)
{
    switch (event.second) {
        case types::InputEvent::AKEY_F8:
            display = nextLib();
            loadDisplay(display.c_str());
            return 0;
        case types::InputEvent::AKEY_ESCAPE:
            if (strcmp(_gameName, "MENU") == 0)
                _quit = true;
            return 1;
        case types::InputEvent::AKEY_F12:
            loadGame(game.c_str());
            return 0;
        default:
            return 0;
    }
}

/**
 * @brief Getting the name of a library.
 * @details Using a library path and getting its name.
 * @return A string containing the name of the library if it exists
 */
std::string arcade::core::Core::getLibName(std::string display)
{
    for (auto it = _displays.begin(); it != _displays.end(); it++) {
        if (it->second == display)
            return it->first;
    }
    return "";
}

/**
 * @brief Main game loop.
 * @details Central loop that forwards input events from the graphical libraries to the game,
 * and sends the entities to display back to the graphical libraries.
 * @return void
 */
void arcade::core::Core::runSingleGame(std::string &game, std::string &display)
{
    std::string ret;

    loadGame(game.c_str());

    if (_libName[0] == '\0' || _libName != getLibName(display))
        loadDisplay(display.c_str());

    while (!_game->isGameOver()) {
        auto event = _display->event();

        if (handleInputs(game, display, event) == 1)
            break;

        _game->update(event);
        _display->draw(_game->getEntities());
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP));
    }

    if (strcmp(_gameName, "MENU") == 0) {
        auto tmp_game = utils::getFunction<STRING_CAST>("getSelectedGame", _gameHandle)();
        auto tmp_display = utils::getFunction<STRING_CAST>("getSelectedDisplay", _gameHandle)();

        game = strcmp(tmp_game, "") == 0 ? game : tmp_game;
        display = strcmp(tmp_display, "") == 0 ? display : tmp_display;
    } else
        game = "lib/arcade_menu.so";
}

/**
 * @brief Main loop of the Arcade program.
 * @details This loop launches the game loops and starts a new one
 * when the previous game ends.
 * @return void
 */
void arcade::core::Core::run(const char *display)
{
    std::string new_display = std::string(display);
    std::string game = "lib/arcade_pacman.so";

    while (!_quit)
        runSingleGame(game, new_display);

    if (_game != nullptr) {
        utils::getFunction<GAME_DESTROY>("destroy", _gameHandle)(_game.release());
        utils::unload_dll_so(_gameHandle);
    }
    if (_display != nullptr) {
        utils::getFunction<DISPLAY_DESTROY>("destroy", _displayHandle)(_display.release());
        utils::unload_dll_so(_displayHandle);
    }
}

/**
 * @brief Getter for _games.
 * @details Getter for _games.
 * @return Undordered map that contains the game names, and the game paths.
 */
std::unordered_map<std::string, std::string> arcade::core::Core::getGames(void) const
{
    return _games;
}

/**
 * @brief Getter for _displays.
 * @details Getter for _displays.
 * @return Undordered map that contains the display modules names, and the display modules paths.
 */
std::unordered_map<std::string, std::string> arcade::core::Core::getDisplays(void) const
{
    return _displays;
}
