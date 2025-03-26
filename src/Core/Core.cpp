/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Core
*/

#include "Core.hpp"
#include "../Utils/GetLib.hpp"

arcade::core::Core::Core()
{

}

arcade::core::Core::~Core()
{

}

void arcade::core::Core::run(const char *display)
{
    void *game_handle = utils::load_dll_so("./lib/arcade_menu.so");
    void *display_handle = utils::load_dll_so(display);
}

void arcade::core::Core::update()
{

}

void arcade::core::Core::draw()
{

}
