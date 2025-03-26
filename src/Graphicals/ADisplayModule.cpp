/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ADisplayModule.cpp
*/

#include "ADisplayModule.hpp"

/*
 * public
 */

arcade::display::ADisplayModule::~ADisplayModule()
{
}

/*
 * NOTE: override the following methods in inheritance
 */

/*
 * INFO:
 * this is where you initialize game attributes
 */

void arcade::display::ADisplayModule::init()
{
    //
}

/*
 * INFO:
 * this is where you declare things you draw (no inf loop, it is handle by the Core)
 */

void arcade::display::ADisplayModule::draw(__attribute__((unused)) Entities entities)
{
    //
}

/*
 * INFO:
 * this is where you declare events
 */
std::vector<arcade::types::InputEvent> arcade::display::ADisplayModule::event()
{
    return std::vector<types::InputEvent>{types::KEY_UNKNOWN};
}

/*
 * INFO:
 * this is where you destroy game attributes
 */
void arcade::display::ADisplayModule::stop()
{
}

/*
 * getters
 */

const std::string &arcade::display::ADisplayModule::getName() const
{
    return _name;
}
