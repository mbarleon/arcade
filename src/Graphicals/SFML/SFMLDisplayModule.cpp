/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SFMLDisplayModule
*/

#include "SFMLDisplayModule.hpp"

arcade::display::SFMLDisplayModule::SFMLDisplayModule()
{
    _win.create(sf::VideoMode(VIDEO_SIZE.first, VIDEO_SIZE.second), _name, sf::Style::Default);
    sf::Listener::setGlobalVolume(50);
}

arcade::display::SFMLDisplayModule::~SFMLDisplayModule()
{
}

void arcade::display::SFMLDisplayModule::draw(Entities entities)
{
}

std::pair<arcade::types::Position, arcade::types::InputEvent> arcade::display::SFMLDisplayModule::event()
{
    _mouse = sf::Mouse::getPosition();

    if (_win.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return std::make_pair(types::Position{_mouse.x, _mouse.y}, types::KEY_ESCAPE);
        else if (_event.type == sf::Event::KeyPressed)
            return std::make_pair(types::Position{_mouse.x, _mouse.y}, (types::InputEvent)_event.key); // MISSING CAST
        else if (_event.type == sf::Event::Resized)
            _win.setView(sf::View(sf::FloatRect(0, 0, _event.size.width, _event.size.height)));
        // MOUSE EVENT
        this->~SFMLDisplayModule();
    }
    return std::make_pair(types::Position{_mouse.x, _mouse.y}, types::KEY_UNKNOWN);
}
