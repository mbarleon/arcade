/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "../AGame.hpp"
#include <unordered_map>

/**
 * @file Menu.hpp
 * @brief Declares the Menu class, used to display and navigate game and library options.
 * @author ...
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This header defines the Menu class, which is responsible for displaying the graphical interface
 * that allows the user to choose a game and a graphical library. It includes logic for navigation,
 * selection, and rendering of entities using a unified API.
 *
 * The Menu handles:
 * - Displaying game and library names.
 * - Highlighting the selected options.
 * - Handling keyboard/mouse events.
 *
 * @see arcade::game::Menu
 */

namespace arcade::game {
    /**
     * @class Menu
     * @brief Implements the game menu interface for Arcade.
     * @details The Menu class displays a graphical interface where the user can navigate through
     * available games and graphical libraries. It manages user input, updates selection states,
     * and renders all relevant UI elements.
     *
     * The class interacts with the Core to retrieve available modules,
     * and uses `addEntity()` to prepare elements for rendering by the display library.
     *
     * @see arcade::core::Core, arcade::game::Menu::update
     */
    class Menu : public arcade::game::AGame {
        public:
            Menu();
            ~Menu() {};

            void update(const std::pair<types::Position, types::InputEvent> event) override;
            void displaySelectedOptionGame();
            void displayText();
            void displaySelectedOptionLib();

        protected:
        private:
            std::unordered_map<std::string, std::string> _gam;
            std::unordered_map<std::string, std::string> _lib;
            int _nbrGames;
            int _nbrLib;
            arcade::types::color_t _color;
            static constexpr std::pair VIDEO_SIZE = {30, 40};


            int _selectedLib;
            int _selectedGam;
            bool _selected;
    };
}
#endif /* !MENU_HPP_ */
