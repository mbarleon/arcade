/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** __Name__Game
*/

#pragma once
#include "AGame.hpp"
#include <cstring>

namespace arcade::game {
    class __Name__Game : public AGame {
        public:
            __Name__Game();
            ~__Name__Game() override;

            void update(const std::pair<types::Position, types::InputEvent> event) override;
    };
};
