/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** AGame
*/

#ifndef AGAME_HPP_
    #define AGAME_HPP_
    #include "IGame.hpp"

namespace arcade::game {
    class AGame : public IGame {
        public:
            AGame();
            virtual ~AGame() = 0;

            void update(const std::pair<types::Position, types::InputEvent>) override;

            /* getters */
            const Entities &getEntities() const override;
            int getScore() const override;
            bool isGameOver() const override;

            /* setters */
            void setGameOver(bool state) override;

            /* entities */
            void addEntity(types::EntityType type, types::EntityDraw draw, types::Position pos,
                char c, uint32_t color) override;
            void removeEntityAt(const types::Position &pos) override;
            types::Entity *getEntityAt(const types::Position &pos) override;
            void clearEntities() override;

        protected:
            int _score;
            bool _gameOver;
            Entities _entities;
            std::unordered_map<types::Position, types::Entity *> _entitiesIndex;
    };
};

#endif /* !AGAME_HPP_ */
