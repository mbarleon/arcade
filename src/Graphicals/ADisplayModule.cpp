/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** ADisplayModule
*/

#include "ADisplayModule.hpp"

void arcade::display::ADisplayModule::init()
{
}

void arcade::display::ADisplayModule::draw(Entities entities)
{
}

std::pair<arcade::types::Position, arcade::types::InputEvent> arcade::display::ADisplayModule::event()
{
    return std::pair<types::Position, types::InputEvent>();
}

void arcade::display::ADisplayModule::stop()
{
}

const std::string &arcade::display::ADisplayModule::getName() const
{
    return _name;
}
