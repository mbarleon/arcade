/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** AGame.hpp
*/

#pragma once

#include "IGame.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace arcade::game {
    class AGame : public IGame {
        public:
            AGame() = default;
            virtual ~AGame() = 0;

            void init() override;
            void update() override;
            void stop() override;

            const std::string &getName() const override;
            const std::unordered_map<types::EntityDraw, types::Entity> &getEntities() const override;
            const std::pair<uint32_t, uint32_t> &getMapSize() const override;

            void addEntity(types::EntityType type, types::EntityDraw draw, types::Position pos, char c,
                uint32_t color) override;
            void removeEntityAt(const types::Position &pos) override;
            types::Entity *getEntityAt(const types::Position &pos) override;

            bool isGameOver() const override;
            void handleInput(const std::vector<types::InputEvent> event) override;
            int getScore() const override;

        protected:
            void setGameOver(bool gameOver);
            void clearEntities();

            std::unique_ptr<IGame> _module;
            std::string _name;

            int _score;
            bool _gameOver;

            std::unordered_map<types::EntityDraw, types::Entity> _entities;
            std::pair<uint32_t, uint32_t> _mapSize;
    };
};
