/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanFactory
*/

/**
 * @file PacmanFactory.cpp
 * @brief Factory functions to create and destroy the Pacman game instance.
 * @author Jason KOENIG
 * @version 1.0
 * @date 2025-04-14
 *
 * @details
 * This file implements the C interface expected by the Core to dynamically load
 * the Pacman game shared object. It defines:
 * - `create()` to instantiate the game
 * - `destroy()` to delete it
 * - `getType()` to indicate the module type (`GAME`)
 * - `getName()` to return the name of the game
 *
 * These functions are used by the Arcade Core loader and allow the Pacman game
 * to be treated as a plugin.
 */

#include "PacmanGame.hpp"

#include "Assets/ghosts/green_bottom.hpp"
#include "Assets/ghosts/orange_bottom.hpp"
#include "Assets/ghosts/pink_bottom.hpp"
#include "Assets/ghosts/red_bottom.hpp"
#include "Assets/ghosts/vulnerable_bottom.hpp"
#include "Assets/ghosts/dead.hpp"
#include "Assets/map/pacgum.hpp"
#include "Assets/map/gum.hpp"
#include "Assets/map/map.hpp"
#include "Assets/pac/pac_bottom_1.hpp"
#include "Assets/life.hpp"
#include "Assets/fruits/apple.hpp"
#include "Assets/fruits/banana.hpp"
#include "Assets/fruits/cherries.hpp"
#include "Assets/fruits/key.hpp"
#include "Assets/fruits/pineapple.hpp"
#include "Assets/fruits/potion.hpp"

extern "C" {
    arcade::game::IGame *create(void)
    {
        return new arcade::game::PacmanGame();
    }

    void destroy(arcade::game::IGame *game)
    {
        delete game;
    }

    arcade::types::LibType getType(void)
    {
        return arcade::types::GAME;
    }

    const char *getName()
    {
        return "PACMAN";
    }
}

/**
 * @brief Constructor for the PacmanGame class.
 * @details Initializes all game-related data and entities. This includes:
 * - Setting initial counters (score, level, timers).
 * - Adding the background sprite.
 * - Initializing the game map and all entities (player, ghosts, food, etc.).
 * - Loading the high score from file.
 * - Displaying the initial score text and extra life icons.
 * - Setting the player's starting position.
 *
 * This constructor prepares the entire game to be ready for the first frame.
 */
arcade::game::PacmanGame::PacmanGame() : _dotCpt(0), _level(1), _timer(0), _fruitTimer(0)
{
    addEntity(types::EMPTY, types::SPRITE, getPosition(0, 0),
    pacman::WALL, getEntityColor(pacman::WALL).color, "",
    {.key = "Background", .assets = map_png, .length = map_png_len});

    initGameMap();
    initGameEntities();
    loadHighScore();

    addEntity(types::EMPTY, types::TEXT, (types::Position){2, 2}, ' ',
    getRGBA(255, 255, 255, 255).color,
    "level 1   score 0   high score " + std::to_string(_highScore));

    addEntity(types::EMPTY, types::SPRITE, (types::Position){3, 37}, pacman::LIFE,
    getRGBA(255, 255, 255, 255).color, "", getEntitySprite(pacman::LIFE));

    addEntity(types::EMPTY, types::SPRITE, (types::Position){1, 37}, pacman::LIFE,
    getRGBA(255, 255, 255, 255).color, "", getEntitySprite(pacman::LIFE));

    _playerStartPos = getPosition(16, 13);
}

/**
 * @brief Destructor for the PacmanGame class.
 * @details Ensures that the current high score is saved to disk before the game is destroyed,
 * and clears all entities from the game state.
 */
arcade::game::PacmanGame::~PacmanGame()
{
    saveHighScore();
    clearEntities();
}

/**
 * @brief Returns the score value of a food or ghost entity.
 * @details Determines the number of points to award based on the type of entity collected:
 * - Basic food (`GUM`) gives 10 points and increments the dot counter.
 * - Power food (`GUM2`) gives 50 points, resets ghost kill chain, and sets all ghosts to FRIGHTENED.
 * - Fruits (e.g., apple, banana, etc.) give increasing point values.
 * - If a ghost is eaten (in FRIGHTENED mode), the score depends on the current kill chain:
 *   200, 400, 800, or 1600 points depending on how many ghosts have been eaten in a row.
 *
 * The dot counter `_dotCpt` and `_remainingDots` are updated when food is eaten.
 *
 * @param food The character representing the food or ghost entity.
 * @return The score value associated with the collected entity.
 */
int arcade::game::PacmanGame::getFoodValue(char food)
{
    switch (food) {
        case pacman::GUM:
            ++_dotCpt;
            --_remainingDots;
            return 10;
        case pacman::GUM2:
            ++_dotCpt;
            --_remainingDots;
            _player.setKillRow(0);
            setGhostsFrightened();
            return 50;
        case pacman::APPLE:
            return 200;
        case pacman::BANANA:
            return 500;
        case pacman::CHERRIES:
            return 800;
        case pacman::PINEAPPLE:
            return 1500;
        case pacman::POTION:
            return 3000;
        case pacman::KEY:
            return 5000;
        default:
            break;
    }
    if (food != pacman::PINKY && food != pacman::CLYDE &&
    food != pacman::BLINKY && food != pacman::INKY)
        return 0;
    switch (_player.getKillRow()) {
        case 0:
            return 200;
        case 1:
            return 400;
        case 2:
            return 800;
        default:
            return 1600;
    }
    refreshScore();
}

/**
 * @brief Maps a character to its corresponding EntityType.
 * @details Translates a character from the static Pac-Man map to the internal
 * EntityType used for game logic and rendering.
 *
 * The conversion is as follows:
 * - `WALL` → `types::WALL`
 * - `GUM`, `GUM2` → `types::FOOD`
 * - `DOOR` → `types::OBSTACLE`
 * - Anything else → `types::EMPTY`
 *
 * @param c The character representing the entity in the static map.
 * @return The corresponding EntityType used in the game.
 */
arcade::types::EntityType arcade::game::PacmanGame::getEntityType(char c)
{
    switch (c) {
        case pacman::WALL:
            return types::WALL;
        case pacman::GUM:
            return types::FOOD;
        case pacman::GUM2:
            return types::FOOD;
        case pacman::DOOR:
            return types::OBSTACLE;
        default:
            return types::EMPTY;
    }
}

/**
 * @brief Maps a character to its corresponding EntityDraw type.
 * @details Determines how the given entity should be rendered by the graphics libraries.
 *
 * The conversion is as follows:
 * - `GUM`, `GUM2` → `types::SPRITE`
 * - Anything else → `types::NONE` (no specific draw instruction)
 *
 * @param c The character representing the entity in the static map.
 * @return The corresponding EntityDraw value used for rendering.
 */
arcade::types::EntityDraw arcade::game::PacmanGame::getEntityDraw(char c)
{
    switch (c) {
        case pacman::GUM:
            return types::SPRITE;
        case pacman::GUM2:
            return types::SPRITE;
        default:
            return types::NONE;
    }
}

/**
 * @brief Returns the display color associated with a specific entity character.
 * @details Associates each entity (ghosts, Pac-Man, etc.) with a specific RGBA color:
 * - `PAC` → Yellow (255, 255, 0, 255)
 * - `BLINKY` → Red (255, 0, 0, 255)
 * - `INKY` → Green (0, 255, 0, 255)
 * - `PINKY` → Pink (255, 192, 203, 255)
 * - `CLYDE` → Orange (255, 165, 0, 255)
 * - `VULNERABLE` → Blue (0, 0, 255, 255)
 * - Any other character → White (255, 255, 255, 255)
 *
 * This is used to color entities in rendering, including sprites and text fallback.
 *
 * @param c The character representing the entity.
 * @return The color value in `color_t` format (RGBA).
 */
arcade::types::color_t arcade::game::PacmanGame::getEntityColor(char c)
{
    switch (c) {
        case pacman::PAC:
            return getRGBA(255, 255, 0, 255);
        case pacman::BLINKY:
            return getRGBA(255, 0, 0, 255);
        case pacman::INKY:
            return getRGBA(0, 255, 0, 255);
        case pacman::PINKY:
            return getRGBA(255, 192, 203, 255);
        case pacman::CLYDE:
            return getRGBA(255, 165, 0, 255);
        case pacman::VULNERABLE:
            return getRGBA(0, 0, 255, 255);
        default:
            return getRGBA(255, 255, 255, 255);
    }
}

/**
 * @brief Returns the sprite associated with a specific entity character.
 * @details Maps each character from the static Pac-Man map to a corresponding
 * sprite structure, containing a unique key, raw image data, and its size.
 *
 * Sprite mapping includes:
 * - `GUM` → Small food sprite
 * - `GUM2` → Power-up food (Pac-Gum)
 * - `LIFE` → Extra life icon
 * - `PAC`, `BLINKY`, `INKY`, `PINKY`, `CLYDE` → Default downward-facing sprites for each character
 * - `DEAD` → Eaten ghost sprite
 * - `VULNERABLE` → Frightened mode ghost sprite
 *
 * If the character does not match any known entity, an empty sprite is returned.
 *
 * @param c The character representing the entity.
 * @return The corresponding `Sprite` structure, or an empty sprite if none matches.
 *
 * @see arcade::types::Sprite
 */
arcade::types::Sprite arcade::game::PacmanGame::getEntitySprite(char c)
{
    switch (c) {
        case pacman::GUM:
            return {.key = "Pacman_Gum", .assets = gum_png, .length = gum_png_len};
        case pacman::GUM2:
            return {.key = "Pacman_Gum2", .assets = pacgum_png, .length = pacgum_png_len};
        case pacman::LIFE:
            return {.key = "Pacman_Life", .assets = life_png, .length = life_png_len};
        case pacman::PAC:
            return {.key = "Pacman_Pac", .assets = pac_bottom_1_png, .length = pac_bottom_1_png_len};
        case pacman::BLINKY:
            return {.key = "Pacman_Blinky", .assets = red_bottom_png, .length = red_bottom_png_len};
        case pacman::PINKY:
            return {.key = "Pacman_Pinky", .assets = pink_bottom_png, .length = pink_bottom_png_len};
        case pacman::INKY:
            return {.key = "Pacman_Inky", .assets = green_bottom_png, .length = green_bottom_png_len};
        case pacman::CLYDE:
            return {.key = "Pacman_Clyde", .assets = orange_bottom_png, .length = orange_bottom_png_len};
        case pacman::DEAD:
            return {.key = "Pacman_Eaten", .assets = dead_png, .length = dead_png_len};
        case pacman::VULNERABLE:
            return {.key = "Pacman_Vulnerable", .assets = vulnerable_bottom_png,
                .length = vulnerable_bottom_png_len};
        default:
            return {};
    }
}

/**
* @brief Converts map coordinates to screen coordinates.
* @details Adjusts the Y-axis value by adding a vertical margin
* (`MAP_MARGIN_TOP`) to fit the game map into the graphical window layout.
*
* This is used when placing entities so they appear correctly offset from the top of the screen.
*
* @param y The Y-coordinate in the map (tile-based).
* @param x The X-coordinate in the map (tile-based).
* @return A `Position` representing the screen-relative coordinates
*/
arcade::types::Position arcade::game::PacmanGame::getPosition(int y, int x)
{
    types::Position pos;

    pos.x = x;
    pos.y = y + MAP_MARGIN_TOP;
    return pos;
}

/**
 * @brief Retrieves the first entity that matches a given display character.
 * @details Iterates through all entities grouped by draw type to find the first one
 * whose `display_char` matches the provided character.
 *
 * This function is primarily used to locate a unique game entity (like a ghost or Pac-Man)
 * based on its character representation.
 *
 * @param c The character used to identify the target entity.
 * @return A pointer to the matching `Entity`, or `nullptr` if not found.
 *
 * @see types::Entity
 */
arcade::types::Entity *arcade::game::PacmanGame::getEntityAtByChar(char c)
{
    for (auto &pair : _entities) {
        auto &entitiesVec = pair.second;

        for (auto it = entitiesVec.begin(); it != entitiesVec.end(); it++)
            if ((*it).display_char == c)
                return &(*it);
    }
    return nullptr;
}

/**
 * @brief Returns the current game cycle time based on the level.
 * @details The cycle time determines the pacing of ghost updates and other timed events.
 * It decreases as the player progresses to higher levels, making the game faster and more difficult.
 *
 * Level thresholds:
 * - > 8 → cycle time = 2
 * - > 6 → cycle time = 3
 * - > 4 → cycle time = 4
 * - > 2 → cycle time = 5
 * - ≤ 2 → cycle time = 6
 *
 * @return The number of ticks to wait between each logic update cycle.
 */
int arcade::game::PacmanGame::getCycleTime()
{
    if (_level > 8)
        return 2;
    if (_level > 6)
        return 3;
    if (_level > 4)
        return 4;
    if (_level > 2)
        return 5;
    return 6;
}

/**
 * @brief Removes the first entity matching a specific display character.
 * @details Iterates through all entity groups and erases the first entity found
 * whose `display_char` matches the provided character. Once removed, the function exits.
 *
 * This is typically used to delete unique entities such as lives, ghosts, or the player,
 * identified by their character representation.
 *
 * @param c The character used to identify the entity to remove.
 */
void arcade::game::PacmanGame::removeEntityAtByChar(char c)
{
    for (auto &pair : _entities) {
        auto &entitiesVec = pair.second;
        for (auto it = entitiesVec.begin(); it != entitiesVec.end(); ++it)
            if ((*it).display_char == c) {
                entitiesVec.erase(it);
                return;
            }
    }
}

/**
 * @brief Resets all main game entities to their initial positions and states.
 * @details Repositions the player and each ghost (Blinky, Pinky, Inky, Clyde)
 * to their default spawn points on the map. Also:
 * - Resets the direction of all entities.
 * - Sets all ghosts to `SCATTER` mode.
 *
 * This function is typically called after the player loses a life, to restart the round
 * without restarting the full game.
 *
 * @see getEntityAtByChar()
 * @see getPosition()
 * @see pacman::GhostMode
 */
void arcade::game::PacmanGame::resetGameEntities()
{
    _player.setPosition(16, 13);
    getEntityAtByChar(pacman::PAC)->pos = getPosition(16, 13);
    _blinky.setPosition(11, 13);
    getEntityAtByChar(pacman::BLINKY)->pos = getPosition(11, 13);
    _pinky.setPosition(14, 12);
    getEntityAtByChar(pacman::PINKY)->pos = getPosition(14, 12);
    _inky.setPosition(14, 13);
    getEntityAtByChar(pacman::INKY)->pos = getPosition(14, 13);
    _clyde.setPosition(14, 14);
    getEntityAtByChar(pacman::CLYDE)->pos = getPosition(14, 14);

    _player.setDirection(types::LEFT);
    _blinky.setDirection(types::UP);
    _pinky.setDirection(types::UP);
    _inky.setDirection(types::UP);
    _clyde.setDirection(types::UP);

    _blinky.setMode(pacman::SCATTER);
    _pinky.setMode(pacman::SCATTER);
    _inky.setMode(pacman::SCATTER);
    _clyde.setMode(pacman::SCATTER);
}

/**
 * @brief Initializes all main entities for the Pac-Man game.
 * @details Creates and places the player (`PAC`) and the four ghosts
 * (`BLINKY`, `PINKY`, `INKY`, `CLYDE`) on the map using their corresponding
 * position, color, and sprite.
 *
 * All entities are added via `addEntity()` with appropriate types:
 * - `PLAYER` for Pac-Man
 * - `ENEMY` for each ghost
 *
 * After creation, the function calls `resetGameEntities()` to set
 * their initial direction and behavior.
 *
 * @see addEntity()
 * @see resetGameEntities()
 */
void arcade::game::PacmanGame::initGameEntities()
{
    addEntity(types::PLAYER, types::SPRITE, getPosition(16, 13), pacman::PAC,
    getEntityColor(pacman::PAC).color, "", getEntitySprite(pacman::PAC));

    addEntity(types::ENEMY, types::SPRITE, getPosition(12, 13), pacman::BLINKY,
    getEntityColor(pacman::BLINKY).color, "", getEntitySprite(pacman::BLINKY));

    addEntity(types::ENEMY, types::SPRITE, getPosition(14, 12), pacman::PINKY,
    getEntityColor(pacman::PINKY).color, "", getEntitySprite(pacman::PINKY));

    addEntity(types::ENEMY, types::SPRITE, getPosition(14, 13), pacman::INKY,
    getEntityColor(pacman::INKY).color, "", getEntitySprite(pacman::INKY));

    addEntity(types::ENEMY, types::SPRITE, getPosition(14, 14), pacman::CLYDE,
    getEntityColor(pacman::CLYDE).color, "", getEntitySprite(pacman::CLYDE));

    resetGameEntities();
}

/**
 * @brief Initializes the Pac-Man level map.
 * @details Iterates through the static `pacMap` layout and creates entities for
 * all visible tiles, such as walls, food, power-ups, and doors. Each entity is
 * assigned the correct type, draw method, color, and sprite.

 * Additionally:
 * - Increments `_remainingDots` for each food entity (`GUM` or `GUM2`),
 *   used to track progression and level completion.
 * - Skips empty tiles that have no visual or logical significance.

 * @see pacMap
 * @see getEntityDraw()
 * @see getEntityType()
 * @see addEntity()
 */
void arcade::game::PacmanGame::initGameMap()
{
    _remainingDots = 0;

    for (int y = 0; y < MAP_SIDE; ++y)
        for (int x = 0; x < MAP_SIDE; ++x) {
            types::EntityDraw entityDraw = getEntityDraw(pacman::pacMap[y][x]);
            types::EntityType entityType = getEntityType(pacman::pacMap[y][x]);

            if (entityType == types::FOOD)
                ++_remainingDots;
            if (!(entityDraw == types::NONE && entityType == types::EMPTY))
                addEntity(entityType, entityDraw, getPosition(y, x),
                pacman::pacMap[y][x], getEntityColor(pacman::pacMap[y][x]).color, "",
                getEntitySprite(pacman::pacMap[y][x]));
        }
}

/**
 * @brief Spawns a bonus food item at the player's starting position.
 * @details This function generates a fruit or bonus item at the center of the map
 * (player start position) depending on the current game level.
 *
 * Behavior:
 * - If an entity already exists at the target position, no food is generated.
 * - Resets the fruit timer.
 * - Selects the food to spawn based on the level:
 *   - 1 → Apple
 *   - 2 → Banana
 *   - 3 → Cherries
 *   - 4 → Pineapple
 *   - 5 → Potion
 *   - ≥6 → Key
 *
 * The generated item is added to the game as a `FOOD` entity with a corresponding sprite.
 *
 * @see addEntity()
 * @see _playerStartPos
 */
void arcade::game::PacmanGame::generateFood()
{
    if (getEntityAt(_playerStartPos))
        return;
    _fruitTimer = 0;
    switch (_level) {
        case 1:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::APPLE,
            getEntityColor(pacman::APPLE).color, "",
            {.key = "Apple", .assets = apple_png, .length = apple_png_len});
            return;
        case 2:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::BANANA,
            getEntityColor(pacman::BANANA).color, "",
            {.key = "Banana", .assets = banana_png, .length = banana_png_len});
            return;
        case 3:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::CHERRIES,
            getEntityColor(pacman::CHERRIES).color, "",
            {.key = "Cherries", .assets = cherries_png, .length = cherries_png_len});
            return;
        case 4:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::PINEAPPLE,
            getEntityColor(pacman::PINEAPPLE).color, "",
            {.key = "Pineapple", .assets = pineapple_png, .length = pineapple_png_len});
            return;
        case 5:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::POTION,
            getEntityColor(pacman::POTION).color, "",
            {.key = "Potion", .assets = potion_png, .length = potion_png_len});
            return;
        default:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::KEY,
            getEntityColor(pacman::KEY).color, "",
            {.key = "Key", .assets = key_png, .length = key_png_len});
            return;
    }
}

/**
 * @brief Handles the transition between ghost behavior modes based on timers and position.
 * @details This function updates the mode of a ghost depending on its current state and elapsed time:
 *
 * - **SCATTER → CHASE**: After `getCycleTime() * TIME_1_SEC` ticks, the ghost switches to CHASE mode.
 * - **CHASE → SCATTER**: After `(10 - getCycleTime()) * TIME_1_SEC` ticks, the ghost returns to SCATTER mode.
 * - **FRIGHTENED → Last Mode**: After 10 seconds, the ghost returns to its previous mode and skin is restored.
 * - **EATEN → Last Mode**: If the ghost reaches the ghost house center (13,14), it is revived and its appearance is reset.
 *
 * The function is typically called once per game loop iteration to manage state transitions.
 *
 * @param ghost Reference to the ghost whose mode should be checked and possibly updated.
 *
 * @see pacman::GhostMode
 * @see Ghost::loadLastMode()
 * @see restoreGhostSkin()
 */
void arcade::game::PacmanGame::exitGhostSpecialModes(pacman::Ghost &ghost)
{
    pacman::GhostMode mode = ghost.getMode();
    size_t timer = ghost.getTimer();
    types::Position &pos = ghost.getPosition();

    ++timer;
    switch (mode) {
        case pacman::SCATTER:
            if (timer % (getCycleTime() * TIME_1_SEC) == 0) {
                ghost.setMode(pacman::CHASE);
                ghost.setTimer(0);
                return;
            }
            break;
        case pacman::CHASE:
            if (timer % ((10 - getCycleTime()) * TIME_1_SEC) == 0) {
                ghost.setMode(pacman::SCATTER);
                ghost.setTimer(0);
                return;
            }
            break;
        case pacman::FRIGHTENED:
            if (timer % (TIME_1_SEC * 10) == 0) {
                ghost.setTimer(0);
                restoreGhostSkin(ghost.getId());
                ghost.loadLastMode();
                return;
            }
            break;
        case pacman::EATEN:
            if (pos.x == 13 && pos.y == 14) {
                ghost.loadLastMode();
                restoreGhostSkin(ghost.getId());
            }
            return;
        default:
            return;
    }
    ghost.setTimer(timer);
}

/**
 * @brief Puts all eligible ghosts into FRIGHTENED mode.
 * @details This function updates the state and appearance of all ghosts
 * (Blinky, Pinky, Inky, Clyde) that are currently not in `EATEN` or `FRIGHTENED` mode:
 *
 * - Changes their mode to `FRIGHTENED`
 * - Updates their skin to the vulnerable appearance (`pacman::VULNERABLE`)
 *
 * Ghosts already in FRIGHTENED or EATEN mode are ignored.
 * This function is typically called when the player eats a power-up (`GUM2`).
 *
 * @see setGhostSkin()
 * @see pacman::GhostMode
 */
void arcade::game::PacmanGame::setGhostsFrightened()
{
    if (_blinky.getMode() != pacman::EATEN &&
    _blinky.getMode() != pacman::FRIGHTENED) {
        setGhostSkin(pacman::BLINKY, pacman::VULNERABLE);
        _blinky.setMode(pacman::FRIGHTENED);
    }
    if (_pinky.getMode() != pacman::EATEN &&
    _pinky.getMode() != pacman::FRIGHTENED) {
        setGhostSkin(pacman::PINKY, pacman::VULNERABLE);
        _pinky.setMode(pacman::FRIGHTENED);
    }
    if (_inky.getMode() != pacman::EATEN &&
    _inky.getMode() != pacman::FRIGHTENED) {
        setGhostSkin(pacman::INKY, pacman::VULNERABLE);
        _inky.setMode(pacman::FRIGHTENED);
    }
    if (_clyde.getMode() != pacman::EATEN &&
    _clyde.getMode() != pacman::FRIGHTENED) {
        setGhostSkin(pacman::CLYDE, pacman::VULNERABLE);
        _clyde.setMode(pacman::FRIGHTENED);
    }
}

/**
 * @brief Changes the skin (color and sprite) of a ghost entity.
 * @details This function updates both the `color` and `sprite` fields of the ghost
 * identified by its `display_char` to match a new skin character.
 *
 * Typically used to change a ghost's appearance to `VULNERABLE` or `DEAD`.
 *
 * @param c The character representing the ghost (e.g., `BLINKY`, `PINKY`...).
 * @param skin The character representing the new skin (e.g., `VULNERABLE`, `DEAD`...).
 *
 * @see getEntityAtByChar()
 * @see getEntityColor()
 * @see getEntitySprite()
 */
void arcade::game::PacmanGame::setGhostSkin(char c, char skin)
{
    types::Entity *ghost = getEntityAtByChar(c);

    if (ghost) {
        ghost->color = getEntityColor(skin).color;
        ghost->sprite = getEntitySprite(skin);
    }
}

/**
 * @brief Restores a ghost's original appearance.
 * @details This function resets the `color` and `sprite` of the ghost to match
 * its original look based on its character identifier.
 *
 * Used after a ghost exits `FRIGHTENED` or `EATEN` mode.
 *
 * @param c The character representing the ghost (e.g., `BLINKY`, `INKY`...).
 *
 * @see getEntityAtByChar()
 * @see getEntityColor()
 * @see getEntitySprite()
 */
void arcade::game::PacmanGame::restoreGhostSkin(char c)
{
    types::Entity *ghost = getEntityAtByChar(c);

    if (ghost) {
        ghost->color = getEntityColor(c).color;
        ghost->sprite = getEntitySprite(c);
    }
}
