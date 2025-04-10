/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** NCursesDisplayModule
*/

#pragma once

#include <ncurses.h>
#include "ADisplayModule.hpp"

/**
 * @file NCursesDisplayModule.hpp
 * @brief Declaration of the NCursesDisplayModule class and associated definitions.
 * @author mbarleon
 * @version 1.0
 * @date 2025-04-09
 *
 * @details
 * The NCursesDisplayModule class contains all the methods to use ncruses in the arcade.
 */
namespace arcade::display {
    /**
     * @class NCursesDisplayModule
     * @brief Class responsible for containing all the methods to use ncruses in the arcade.
     *
     * @details
     * The NCursesDisplayModule class contains all the methods to use ncruses in the arcade.
     */
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
