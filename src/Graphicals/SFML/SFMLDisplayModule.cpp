/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SFMLDisplayModule
*/

#include "SFMLDisplayModule.hpp"

extern "C" {
    arcade::display::IDisplayModule *create(void)
    {
        return new arcade::display::SFMLDisplayModule();
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
        return "SFML";
    }
}

arcade::display::SFMLDisplayModule::SFMLDisplayModule()
{
    sf::Vector2f pixelSize = {RECTANGLE_SIZE, RECTANGLE_SIZE};

    _win.create(sf::VideoMode(VIDEO_SIZE.first, VIDEO_SIZE.second), "Arcade", sf::Style::Default);
    sf::Listener::setGlobalVolume(50);
    _pixel.setSize(pixelSize);
    _circle.setRadius(CIRCLE_RADIUS);
    _font.loadFromFile("SFPro.OTF");
}

arcade::display::SFMLDisplayModule::~SFMLDisplayModule()
{
}

void arcade::display::SFMLDisplayModule::draw(Entities entities)
{
    sf::Vector2f pos;

    _win.clear();
    for (auto &it : entities) {
        if (it.first == arcade::types::NONE)
            continue;
        for (auto &ti : it.second) {
            pos = {ti.pos.x * RECTANGLE_SIZE, ti.pos.y * RECTANGLE_SIZE};
            if (it.first == arcade::types::RECTANGLE) {
                _pixel.setPosition(pos);
                _pixel.setFillColor((sf::Color)ti.color);
                _win.draw(_pixel);
                continue;
            }
            if (it.first == arcade::types::CIRCLE) {
                _circle.setPosition(pos);
                _circle.setFillColor((sf::Color)ti.color);
                _win.draw(_circle);
                continue;
            }
            if (it.first == arcade::types::SPRITE) {
                if (_sprites.find(ti.sprite.key) == _sprites.end()) {
                    sf::Texture texture;
                    sf::Sprite sprite;
                    _sprites[ti.sprite.key] = std::make_pair(texture, sprite);
                    sf::Texture &texture_ = _sprites.at(ti.sprite.key).first;
                    sf::Sprite &sprite_ = _sprites.at(ti.sprite.key).second;
                    texture_.loadFromMemory(ti.sprite.assets, ti.sprite.length);
                    texture_.setSmooth(false);
                    sprite_.setTexture(texture_);
                }
                sf::Sprite &sprite2_ = _sprites.at(ti.sprite.key).second;
                sprite2_.setPosition(pos);
                _win.draw(sprite2_);
                continue;
            }
            if (it.first == arcade::types::TEXT) {
                if (_textes.find(ti.sprite.key) == _textes.end()) {
                    sf::Text text;
                    _textes[ti.sprite.key] = text;
                    _textes[ti.sprite.key].setFont(_font);
                }
                sf::Text &text_ = _textes.at(ti.sprite.key);
                text_.setFillColor((sf::Color)ti.color);
                text_.setPosition(pos);
                text_.setString(ti.str);
                _win.draw(text_);
            }
        }
    }
    _win.display();
}

std::pair<arcade::types::Position, arcade::types::InputEvent> arcade::display::SFMLDisplayModule::event()
{
    if (!_win.isOpen())
        return std::make_pair(types::Position{0, 0}, types::AKEY_ESCAPE);

    _mouse = sf::Mouse::getPosition();

    if (_win.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return std::make_pair(types::Position{_mouse.x, _mouse.y}, types::AKEY_ESCAPE);
        else if (_event.type == sf::Event::KeyPressed)
            return std::make_pair(types::Position{_mouse.x, _mouse.y}, (types::InputEvent)_event.key.code);
        else if (_event.type == sf::Event::MouseButtonPressed)
            return std::make_pair(types::Position{_mouse.x, _mouse.y}, types::ALEFT_BUTTON);
        // else if (_event.type == sf::Event::Resized)
        //     _win.setView(sf::View(sf::FloatRect(0, 0, _event.size.width, _event.size.height)));
    }
    return std::make_pair(types::Position{_mouse.x, _mouse.y}, types::AKEY_UNKNOWN);
}
