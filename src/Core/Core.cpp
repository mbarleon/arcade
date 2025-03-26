/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Core
*/

#include "Core.hpp"
#include "../Utils/GetLib.hpp"
#include "../Utils/Error.hpp"

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

void arcade::core::Core::runSingleGame(std::string &game, const char *display)
{
    std::string ret;

    load_game(game.c_str());
    load_display(display);

    while (!_game->isGameOver()) {
        _game->update(_display->event());
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
