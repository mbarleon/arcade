/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Menu
*/

#include "Menu.hpp"

#include <iostream>

#include "../../Core/Core.hpp"

/**
 * @file Menu.cpp
 * @brief Declares global variables used to store user selections in the Arcade menu.
 * @author Noé CARABIN (CorpsB)
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This file contains two global variables:
 * - `name` stores the identifier of the game selected by the user.
 * - `lib` stores the identifier of the graphical library selected by the user.
 *
 * These values are modified in the menu logic (e.g., Menu::update()) and are accessed
 * by the core system to load the appropriate modules at runtime.
 *
 * @warning Use of global variables should be minimized; these are justified by architectural constraints.
 *
 * @see arcade::game::Menu::update
 */


/**
 * @brief Name of the selected game.
 * @details This global variable holds the identifier of the game selected from the menu.
 * It is set in Menu::update() after user confirmation.
 */
std::string name;

/**
 * @brief Name of the selected graphical library.
 * @details This global variable holds the identifier of the graphical library selected
 * from the menu. It is set in Menu::update() after user confirmation.
 */
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
        return arcade::types::MENU;
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

/**
 * @brief Constructs the menu.
 * @details Initializes all the necessary attributes for proper menu display, including the list of
 * available games and display libraries. The special "MENU" entry is removed from the games list.
 * It also sets the default color, selection flags, and initial indices.
 *
 * @note The display and game lists are retrieved using arcade::core::Core::getDisplays()
 * and getGames().
 */
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

/**
 * @brief Highlights the currently selected game.
 * @details This function draws a rectangle around the currently selected game option on the screen.
 * The selected game is determined based on user input events and internal selection state.
 */
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

/**
 * @brief Displays all text labels.
 * @details This function renders the names of all available games and graphical libraries
 * on the screen, using text entities.
 */
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

/**
 * @brief Displays the selected graphical library (if applicable).
 * @details This function highlights the currently selected display library with a rectangle,
 * but only if a game has already been selected. It visually frames the user's current choice.
 */
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

/**
 * @brief Updates the menu display and handles user input.
 * @details This function handles navigation input to select games or graphical libraries.
 * It also triggers visual updates by calling other display-related functions such as
 * displayText(), displaySelectedOptionGame(), and displaySelectedOptionLib().
 * When the user confirms their selection (ENTER), the selected game and library are stored.
 *
 * @param event The latest event containing the input type and mouse position.
 * @see displayText, displaySelectedOptionGame, displaySelectedOptionLib
 * @note The ENTER key finalizes the selection; BACKSPACE resets the current choice.
 */
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
