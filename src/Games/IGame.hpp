/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IGame.hpp
*/

#pragma once

#include "Types.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace arcade::game {
    class IGame {
        public:
            virtual ~IGame() = default;

            virtual void init() = 0;
            virtual void update() = 0;
            virtual void stop() = 0;

            virtual const std::string &getName() const = 0;
            virtual const std::unordered_map<types::EntityDraw, types::Entity> &getEntities() const = 0;
            virtual const std::pair<uint32_t, uint32_t> &getMapSize() const = 0;

            virtual bool isGameOver() const = 0;
            virtual void handleInput(const std::vector<types::InputEvent> event) = 0;
            virtual int getScore() const = 0;

            virtual void addEntity(types::EntityType type, types::EntityDraw draw, types::Position pos, char c,
                uint32_t color) = 0;
            virtual void removeEntityAt(const types::Position &pos) = 0;
            virtual types::Entity *getEntityAt(const types::Position &pos) = 0;
    };
};
