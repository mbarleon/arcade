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

            /* core methods */
            void init() override;
            void update(const std::vector<types::InputEvent> events) override;
            void stop() override;

            /* getters */
            const std::string &getName() const override;
            const Entities &getEntities() const override;

            /* entities */
            void addEntity(types::EntityType type, types::EntityDraw draw, types::Position pos, char c,
                uint32_t color) override;
            void removeEntityAt(const types::Position &pos) override;
            types::Entity *getEntityAt(const types::Position &pos) override;

            /* display methods */
            bool isGameOver() const override;
            int getScore() const override;

        protected:
            /* setters */
            void setGameOver(bool gameOver);
            void clearEntities();

            std::unique_ptr<IGame> _module;
            std::string _name;

            int _score;
            bool _gameOver;

            Entities _entities;
            std::unordered_map<types::Position, types::Entity *> _entityIndex;
    };
};// namespace arcade::game
