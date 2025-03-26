/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IGame.hpp
*/

#pragma once

#include "../../include/Types.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace arcade::game {
    class IGame {
        public:
            using Entities = std::unordered_map<types::EntityDraw, std::vector<types::Entity>>;

            virtual ~IGame() = default;

            virtual void init() = 0;
            virtual void update(const std::unordered_map<types::Position, std::vector<types::InputEvent>>) = 0;
            virtual void stop() = 0;

            /* getters */
            virtual const std::string &getName() const = 0;
            virtual const Entities &getEntities() const = 0;

            virtual bool isGameOver() const = 0;
            virtual int getScore() const = 0;

            /* entities */
            virtual void addEntity(types::EntityType type, types::EntityDraw draw, types::Position pos, char c,
                uint32_t color, const std::string str) = 0;
            virtual void removeEntityAt(const types::Position &pos) = 0;
            virtual types::Entity *getEntityAt(const types::Position &pos) = 0;
    };
};// namespace arcade::game
