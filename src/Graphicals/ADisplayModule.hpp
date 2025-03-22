/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ADisplayModule.hpp
*/

#pragma once

#include "IDisplayModule.hpp"

namespace arcade::display {
    class ADisplayModule : public IDisplayModule {
        public:
            ADisplayModule() = default;
            virtual ~ADisplayModule() = 0;

            void init(std::pair<uint32_t, uint32_t> mapSize,
                std::unordered_map<types::EntityDraw, types::Entity> entities) override;
            void draw(std::unordered_map<types::EntityDraw, types::Entity> entities) override;
            std::vector<types::InputEvent> event() override;
            void stop() override;

            const std::string &getName() const override;

        protected:
            std::string _name;
            std::pair<uint32_t, uint32_t> _mapSize;
            std::unordered_map<types::EntityDraw, types::Entity> _entities;
    };
};
