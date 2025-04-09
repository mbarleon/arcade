/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** __Name__DisplayModule
*/

#include "__Name__DisplayModule.hpp"

extern "C" {
    arcade::display::IDisplayModule *create(void)
    {
        return new arcade::display::__Name__DisplayModule();
    }

    void destroy(arcade::display::IDisplayModule *display)
    {
        delete display;
    }

    arcade::types::LibType getType(void)
    {
        return arcade::types::DISPLAY;
    }

    const char *getName()
    {
        return "__NAME__";
    }
}

arcade::display::__Name__DisplayModule::__Name__DisplayModule()
{

}

arcade::display::__Name__DisplayModule::~__Name__DisplayModule()
{

}

void arcade::display::__Name__DisplayModule::draw(Entities entities)
{

}

std::pair<arcade::types::Position, arcade::types::InputEvent> arcade::display::__Name__DisplayModule::event()
{

}
