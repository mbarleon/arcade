/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** AGame
*/

#include "AGame.hpp"

/**
 * @file AGame.hpp
 * @brief Declares the abstract base class for all Arcade games.
 * @author Jason Koenig and Noé Carabin (CorpsB)
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This header defines the AGame class, which serves as a foundation for all game modules
 * in the Arcade project. It provides core functionalities common to all games, such as:
 * - Entity management (add, remove, access)
 * - Score tracking
 * - Game-over state handling
 * Games that inherit from AGame only need to implement their specific gameplay logic
 * in the `update()` method, while benefiting from the built-in utilities.
 * This class is designed to reduce redundancy and enforce consistency across all game implementations.
 *
 * @see arcade::game::IGame
 * @see arcade::game::AGame
 */

/**
 * @brief Constructor of the AGame class.
 * @details Initializes essential game state variables, such as the score and game-over flag,
 * and clears any entities that might be present in the graphical window.
 */
arcade::game::AGame::AGame()
{
    _score = 0;
    _gameOver = false;
    clearEntities();
}

/**
 * @brief Handles input events.
 * @details This function adapts the game state and visuals based on the received event.
 * It is meant to be overridden by derived classes to implement specific game logic.
 * @param event The event received from the graphical library, including mouse position and input type.
 */
void arcade::game::AGame::update([[maybe_unused]] const std::pair<types::Position, types::InputEvent> event)
{
}

/**
 * @brief Returns the list of entities.
 * @details This function provides access to the entity map used for rendering.
 * The map associates positions with entities to be displayed on screen.
 * @return A constant reference to the unordered map of entities.
 * @see arcade::types::Entity
 */
const arcade::game::IGame::Entities &arcade::game::AGame::getEntities() const
{
    return _entities;
}

/**
 * @brief Returns the current score.
 * @details Retrieves the score accumulated by the player during the game.
 * @return The current score as an integer.
 */
int arcade::game::AGame::getScore() const
{
    return _score;
}

/**
 * @brief Checks if the game is over.
 * @details Indicates whether the current game session has ended.
 * @return true if the game is over, false otherwise.
 */
bool arcade::game::AGame::isGameOver() const
{
    return _gameOver;
}

/**
 * @brief Sets the game-over state.
 * @details Updates the internal flag to mark the game as over or still active.
 * @param state true to mark the game as over, false to continue playing.
 */
void arcade::game::AGame::setGameOver(bool state)
{
    _gameOver = state;
}

/**
 * @brief Adds an entity to the render list.
 * @details Adds a new entity to the internal map of entities, which will later be rendered
 * by the graphical libraries. This function centralizes entity creation to ensure consistent
 * display across different rendering backends (e.g., SDL, SFML, Ncurses).
 *
 * @param type The type/nature of the entity (e.g., player, wall, collectible).
 * @param draw The shape or draw method to be used (rectangle, circle, text, sprite).
 * @param pos The position of the entity on the tile-based map.
 * @param c The character used for text-based libraries (e.g., Ncurses).
 * @param color The color to apply to the entity.
 * @param str The text to display if the draw type is TEXT.
 * @param sprite The sprite structure to use if the draw type is SPRITE.
 *
 * @see arcade::types::Entity, arcade::types::EntityDraw
 */
void arcade::game::AGame::addEntity(types::EntityType type, types::EntityDraw draw,
                                    types::Position pos, char c, uint32_t color, const std::string str, const types::Sprite sprite)
{
    types::Entity entity = {.type = type, .pos = pos, .display_char = c,
        .color = color, .str = str, .sprite = sprite};

    _entities[draw].push_back(entity);
}

/**
 * @brief Removes an entity at the given position.
 * @details Deletes an entity located at the specified position from the internal
 * unordered map of entities. If no entity exists at that position, nothing happens.
 * @param pos The position of the entity to remove.
 */
void arcade::game::AGame::removeEntityAt(const types::Position &pos)
{
    for (auto &pair : _entities) {
        auto &entitiesVec = pair.second;
        for (auto it = entitiesVec.begin(); it != entitiesVec.end(); it++) {
            if ((*it).pos == pos) {
                entitiesVec.erase(it);
                return;
            }
        }
    }
}

/**
 * @brief Retrieves the entity at the given position.
 * @details Searches through all entities and returns a pointer to the one
 * located at the specified position, if it exists.
 *
 * @param pos The position of the entity to find.
 * @return A pointer to the entity if found, or nullptr if no match is found.
 */
arcade::types::Entity *arcade::game::AGame::getEntityAt(const types::Position &pos)
{
    for (auto &pair : _entities) {
        auto &entitiesVec = pair.second;
        for (auto it = entitiesVec.begin(); it != entitiesVec.end(); it++) {
            if ((*it).pos == pos) {
                return &(*it);
            }
        }
    }
    return nullptr;
}

/**
 * @brief Clears all entities from the entity map.
 * @details Removes every entity currently stored in the internal structure,
 * effectively resetting the display state.
 */
void arcade::game::AGame::clearEntities()
{
    _entities.clear();
}

/**
 * @brief Returns a filled RGBA color structure.
 * @details Constructs and returns an arcade::types::color_t object using the given
 * red, green, blue, and alpha values.
 *
 * @param r Red component (0–255).
 * @param g Green component (0–255).
 * @param b Blue component (0–255).
 * @param a Alpha (transparency) component (0–255).
 * @return A color structure (`arcade::types::color_t`) containing the specified RGBA values.
 */
arcade::types::color_t arcade::game::AGame::getRGBA(int r, int g, int b, int a)
{
    types::color_t color;

    color.components[types::R] = r;
    color.components[types::G] = g;
    color.components[types::B] = b;
    color.components[types::A] = a;
    return color;
}
