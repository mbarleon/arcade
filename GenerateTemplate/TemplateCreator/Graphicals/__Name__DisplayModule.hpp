/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** __Name__DisplayModule
*/

#pragma once

#include "ADisplayModule.hpp"

namespace arcade::display {
    class __Name__DisplayModule: public ADisplayModule {
        public:
            __Name__DisplayModule();
            ~__Name__DisplayModule();

            void draw(Entities entities) override;
            std::pair<types::Position, types::InputEvent> event() override;
    };
};
