/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IDisplayModule.hpp
*/

#pragma once

#include "Types.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace arcade::display {
    class IDisplayModule {
        public:
            virtual ~IDisplayModule() = default;

            virtual void init(std::pair<uint32_t, uint32_t> mapSize,
                std::unordered_map<types::EntityDraw, types::Entity> entities) = 0;
            virtual void draw(std::unordered_map<types::EntityDraw, types::Entity> entities) = 0;
            virtual std::vector<types::InputEvent> event() = 0;
            virtual void stop() = 0;

            virtual const std::string &getName() const = 0;
    };
};
