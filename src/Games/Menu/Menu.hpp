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


namespace arcade::game {
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
