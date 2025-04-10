/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Menu
*/

#include "Menu.hpp"

#include <iostream>

#include "../../Core/Core.hpp"

std::string name;
std::string lib;

extern "C" {
    arcade::game::IGame *create(void)
    {
        return new arcade::game::Menu();
    }

    void destroy(arcade::game::IGame *game)
    {
        delete game;
    }

    arcade::types::LibType getType(void)
    {
        return arcade::types::GAME;
    }

    const char *getName()
    {
        return "MENU";
    }

    const char *getSelectedGame()
    {
        return name.c_str();
    }

    const char *getSelectedDisplay()
    {
        return lib.c_str();
    }
}

//30*40
arcade::game::Menu::Menu()
{
    arcade::core::Core core;
    this->_lib = core.getDisplays();
    this->_gam = core.getGames();

    this->_nbrLib = this->_lib.size();
    this->_nbrGames = this->_gam.size();
    this->_gam.erase("MENU");
    this->_nbrGames --;
    this->_color = getRGBA(255, 255, 255, 255);
    this->_selected = false;
    this->_selectedGam = 0;
    this->_selectedLib = 0;
}

void arcade::game::Menu::displaySelectedOptionGame() {
    if (!this->_gam.empty()) {
        int posY = static_cast<int>(VIDEO_SIZE.second / 2 / _nbrGames * _selectedGam + VIDEO_SIZE.second / 4);
        int rectWidth = VIDEO_SIZE.first / 2;
        int rectHeight = 5;
        int xMin = 0;
        int xMax = xMin + rectWidth - 1;
        int yMin = posY - rectHeight / 2;
        int yMax = yMin + rectHeight - 1;

        for (int x = xMin; x <= xMax; ++x) {
            this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
                {x, yMin}, '-', this->_color.color, "", {});
            this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
                {x, yMax}, '-', this->_color.color, "", {});
        }

        for (int y = yMin + 1; y < yMax; ++y) {
            this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
                {xMin, y}, '|', this->_color.color, "", {});
            this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
                {xMax, y}, '|', this->_color.color, "", {});
        }

        this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
            {xMin, yMin}, '+', this->_color.color, "", {});
        this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
            {xMax, yMin}, '+', this->_color.color, "", {});
        this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
            {xMin, yMax}, '+', this->_color.color, "", {});
        this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
            {xMax, yMax}, '+', this->_color.color, "", {});
    }
}

void arcade::game::Menu::displayText() {
    int x = 0;
    int y = 0;

    for( auto it : this->_gam) {
        this->addEntity(types::EntityType::EMPTY, types::EntityDraw::TEXT,
            (arcade::types::Position){
                VIDEO_SIZE.first / 6,
                static_cast<int>(VIDEO_SIZE.second / 2 / _gam.size() * x + VIDEO_SIZE.second / 4)
            },
            ' ', this->_color.color, it.first, {});
        x++;
    }
    for( auto it : this->_lib) {
        this->addEntity(types::EntityType::EMPTY, types::EntityDraw::TEXT,
            (arcade::types::Position){
                VIDEO_SIZE.first / 6 * 4,
                static_cast<int>(VIDEO_SIZE.second / 2 / _lib.size() * y + VIDEO_SIZE.second / 4)
            },
            ' ', this->_color.color, it.first, {});
        y++;
    }
}

void arcade::game::Menu::displaySelectedOptionLib() {
    if (!this->_lib.empty()) {
        int posY = static_cast<int>(VIDEO_SIZE.second / 2 / _nbrLib * _selectedLib + VIDEO_SIZE.second / 4);
        int rectWidth = VIDEO_SIZE.first / 2;
        int rectHeight = 5;
        int xMin = VIDEO_SIZE.first / 2;
        int xMax = xMin + rectWidth - 1;
        int yMin = posY - rectHeight / 2;
        int yMax = yMin + rectHeight - 1;

        for (int x = xMin; x <= xMax; ++x) {
            this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
                {x, yMin}, '-', this->_color.color, "", {});
            this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
                {x, yMax}, '-', this->_color.color, "", {});
        }

        for (int y = yMin + 1; y < yMax; ++y) {
            this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
                {xMin, y}, '|', this->_color.color, "", {});
            this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
                {xMax, y}, '|', this->_color.color, "", {});
        }

        // Coins
        this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
            {xMin, yMin}, '+', this->_color.color, "", {});
        this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
            {xMax, yMin}, '+', this->_color.color, "", {});
        this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
            {xMin, yMax}, '+', this->_color.color, "", {});
        this->addEntity(types::EntityType::PLAYER, types::EntityDraw::RECTANGLE,
            {xMax, yMax}, '+', this->_color.color, "", {});
    }

}

void arcade::game::Menu::update(const std::pair<types::Position, types::InputEvent> event)
{
    if (event.second == arcade::types::AKEY_UP) {
        if (this->_selected) {
            this->_selectedLib--;
            if (this->_selectedLib < 0)
                this->_selectedLib = this->_nbrLib - 1;
        } else {
            this->_selectedGam--;
            if (this->_selectedGam < 0)
                this->_selectedGam = this->_nbrGames - 1;
        }
    }
    if (event.second == arcade::types::AKEY_DOWN) {
        if (this->_selected) {
            this->_selectedLib++;
            if (this->_selectedLib >= this->_nbrLib)
                this->_selectedLib = 0;
        } else {
            this->_selectedGam++;
            if (this->_selectedGam >= this->_nbrGames)
                this->_selectedGam = 0;
        }
    }
    if (event.second == arcade::types::AKEY_ENTER) {
        if (this->_selected) {
            int i = 0;
            int j = 0;

            for (auto it = this->_gam.begin(); it != this->_gam.end(); ++it) {
                if (i == this->_selectedGam) {
                    name = it->second;
                    break;
                }
                i++;
            }
            for (auto it = this->_lib.begin(); it != this->_lib.end(); ++it) {
                if (j == this->_selectedLib) {
                    lib = it->second;
                    break;
                }
                j++;
            }
            this->setGameOver(true);
        } else {
            this->_selected = true;
        }
    }
    if (event.second == arcade::types::AKEY_BACKSPACE) {
        this->_selected = false;
    }
    this->clearEntities();
    this->displayText();
    this->displaySelectedOptionGame();
    if (this->_selected) {
        this->displaySelectedOptionLib();
    }
}
