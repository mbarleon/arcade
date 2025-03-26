/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ADisplayModule.hpp
*/

#pragma once

#include "IDisplayModule.hpp"

namespace arcade::display {
    class ADisplayModule : public IDisplayModule
    {
        public:
            ADisplayModule() = default;
            virtual ~ADisplayModule() = 0;

            void init() override;
            void draw(Entities entities) override;
            std::vector<types::InputEvent> event() override;
            void stop() override;

            const std::string &getName() const override;

        protected:
            std::string _name;
    };
};// namespace arcade::display
