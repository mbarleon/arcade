/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** NCursesDisplayModule
*/

#pragma once

#include <ncurses.h>
#include "ADisplayModule.hpp"

namespace arcade::display {
    class NCursesDisplayModule: public ADisplayModule {
        public:
            NCursesDisplayModule();
            ~NCursesDisplayModule();

            void draw(Entities entities) override;
            std::pair<types::Position, types::InputEvent> event() override;
        private:
            types::InputEvent convertKeyPress(int key);
    };
};
