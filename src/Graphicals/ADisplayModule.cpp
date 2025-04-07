/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** ADisplayModule
*/

#include "ADisplayModule.hpp"

arcade::display::ADisplayModule::ADisplayModule() = default;

arcade::display::ADisplayModule::~ADisplayModule() = default;

void arcade::display::ADisplayModule::draw(Entities entities)
{
    (void)entities;
}

std::pair<arcade::types::Position, arcade::types::InputEvent> arcade::display::ADisplayModule::event()
{
    return std::pair<types::Position, types::InputEvent>();
}
