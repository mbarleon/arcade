/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IGame.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "../../include/Types.hpp"

/**
 * @file IGame.hpp
 * @brief Declaration of the game interface class.
 * @author Shared with the partner group
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This class defines the interface that all game classes must implement
 * to be compatible with the Arcade platform.
 * It includes the required functions for integrating a game into the system.
 */

namespace arcade::game {
    /**
     * @class IGame
     * @brief Classe interface de jeu.
     *
     * @details
     * This class defines the interface that all game classes must implement
     * to be compatible with the Arcade platform.
     * It includes the required functions for integrating a game into the system.
     */
    class IGame {
        public:
            using Entities = std::unordered_map<types::EntityDraw, std::vector<types::Entity>>;

            virtual ~IGame() = default;

            virtual void update(const std::pair<types::Position, types::InputEvent>) = 0;

            /* getters */
            virtual const std::string &getName() const = 0;
            virtual const Entities &getEntities() const = 0;
            virtual int getScore() const = 0;
            virtual bool isGameOver() const = 0;

            /* setters */
            virtual void setGameOver(bool state) = 0;

            /* entities */
            virtual void addEntity(types::EntityType type, types::EntityDraw draw, types::Position pos, char c,
                uint32_t color, const std::string str) = 0;
            virtual void removeEntityAt(const types::Position &pos) = 0;
            virtual types::Entity *getEntityAt(const types::Position &pos) = 0;
            virtual void clearEntities() = 0;
    };
};// namespace arcade::game
