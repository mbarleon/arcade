/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** AGame
*/

#ifndef AGAME_HPP_
    #define AGAME_HPP_
    #include "IGame.hpp"

/**
 * @file AGame.hpp
 * @brief Declares the abstract base class for Arcade games.
 * @author Jason Koenig and Carabin Noé (CorpsB)
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This header defines the AGame class, which serves as a common base for all game implementations
 * in the Arcade project. It provides standard logic for entity management, score tracking, and
 * game-over state handling, while delegating the core gameplay logic to derived classes.
 * All games in the project should inherit from AGame and implement game-specific behavior.
 *
 * @see arcade::game::AGame, arcade::game::IGame
 */

namespace arcade::game {
    /**
     * @class AGame
     * @brief Abstract base class for games in the Arcade project.
     * @details Provides a default implementation for entity storage, game state management,
     * and interaction with the rendering engine. Derived game classes can reuse these features
     * and implement specific gameplay logic via the `update()` method.
     * Key features:
     * - Stores entities to be displayed on screen.
     * - Handles game-over logic.
     * - Manages the score.
     * This class implements the IGame interface and is intended to reduce duplication
     * across all game modules.
     *
     * @see IGame
     */
    class AGame : public IGame {
        public:
            AGame();
            virtual ~AGame() {};

            void update(const std::pair<types::Position, types::InputEvent>) override;

            /* getters */
            const Entities &getEntities() const override;
            int getScore() const override;
            bool isGameOver() const override;

            /* setters */
            void setGameOver(bool state) override;

            /* entities */
            void addEntity(types::EntityType type, types::EntityDraw draw, types::Position pos,
                char c, uint32_t color, const std::string str, const types::Sprite sprite = {}) override;
            void removeEntityAt(const types::Position &pos) override;
            types::Entity *getEntityAt(const types::Position &pos) override;
            void clearEntities() override;

        protected:
            types::color_t getRGBA(int r, int g, int b, int a);

            int _score;
            bool _gameOver;
            Entities _entities;
    };
};

#endif /* !AGAME_HPP_ */
