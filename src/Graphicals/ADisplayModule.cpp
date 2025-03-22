/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ADisplayModule.cpp
*/

#include "ADisplayModule.hpp"

/*
 * INFO:
 * this is where you initialize game attributes
 * i recommand you to "super()" call this method in your override to store values:
 *   - ADisplayModule::init(mapSize, entities)
 */
void arcade::display::ADisplayModule::init(std::pair<uint32_t, uint32_t> mapSize,
    std::unordered_map<types::EntityDraw, types::Entity> entities)
{
    _mapSize = mapSize;
    _entities = entities;
}

/*
 * INFO:
 * this is where you declare things you draw (no inf loop, it is handle by the Core)
 */
void arcade::display::ADisplayModule::draw(std::unordered_map<types::EntityDraw, types::Entity> entities)
{
    _entities = entities;
}

/*
 * INFO:
 * this is where you declare events
 */
std::vector<arcade::types::InputEvent> arcade::display::ADisplayModule::event()
{
    return std::vector<types::InputEvent>(types::KEY_UNKNOWN);
}

/*
 * INFO:
 * this is where you destroy game attributes
 */
void arcade::display::ADisplayModule::stop()
{
    _entities.clear();
}

const std::string &arcade::display::ADisplayModule::getName() const
{
    return _name;
}
