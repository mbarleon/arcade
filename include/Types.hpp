/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Types.hpp
*/

#pragma once

/**
 * @file Types.hpp
 * @brief Defines the core data structures and types used across the Arcade project.
 * @author Other Group — updated and extended by our team
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This file contains all common types and structures used by both the display libraries
 * and the game modules. It provides unified representations for positions, entities,
 * input events, colors, and sprites, ensuring consistent communication across components.
 *
 * These types form the foundation of the Arcade architecture and are designed to be
 * lightweight, flexible, and easy to serialize or manipulate.
 *
 * @see arcade::types
 */


#include <cstdint>
#include <functional>
#include <string>

namespace arcade::types {
    /**
     * @enum LibType
     * @brief Identifies the type of a .so file.
     * @details This enum is used to distinguish between different types of shared libraries (.so),
     * allowing the system to differentiate between games and graphical libraries.
     * The `MENU` type is used to treat the menu slightly differently from regular games.
     * @see arcade::core::Core
     */
    enum LibType {
        MENU,    ///< The unique type representing the menu
        GAME,    ///< The type representing a game
        DISPLAY  ///< The type representing a graphical library
    };


    /**
     * @enum InputEvent
     * @brief Event handling enum.
     * @details This enum describes the nature of an input event, such as key presses, clicks, etc.
     * Its structure is based on SFML's event system, with slight modifications to fit the project's needs.
     * Each value is self-explanatory, so we do not provide individual descriptions.
     * @see arcade::display, arcade::game
     */
enum InputEvent {
    AKEY_UNKNOWN = -1,
    AKEY_A = 0,
    AKEY_B,
    AKEY_C,
    AKEY_D,
    AKEY_E,
    AKEY_F,
    AKEY_G,
    AKEY_H,
    AKEY_I,
    AKEY_J,
    AKEY_K,
    AKEY_L,
    AKEY_M,
    AKEY_N,
    AKEY_O,
    AKEY_P,
    AKEY_Q,
    AKEY_R,
    AKEY_S,
    AKEY_T,
    AKEY_U,
    AKEY_V,
    AKEY_W,
    AKEY_X,
    AKEY_Y,
    AKEY_Z,
    AKEY_NUM0,
    AKEY_NUM1,
    AKEY_NUM2,
    AKEY_NUM3,
    AKEY_NUM4,
    AKEY_NUM5,
    AKEY_NUM6,
    AKEY_NUM7,
    AKEY_NUM8,
    AKEY_NUM9,
    AKEY_ESCAPE,
    AKEY_LCONTROL,
    AKEY_LSHIFT,
    AKEY_LALT,
    AKEY_LSYSTEM,
    AKEY_RCONTROL,
    AKEY_RSHIFT,
    AKEY_RALT,
    AKEY_RSYSTEM,
    AKEY_MENU,
    AKEY_LBRACKET,
    AKEY_RBRACKET,
    AKEY_SEMICOLON,
    AKEY_COMMA,
    AKEY_PERIOD,
    AKEY_APOSTROPHE,
    AKEY_SLASH,
    AKEY_BACKSLASH,
    AKEY_GRAVE,
    AKEY_EQUAL,
    AKEY_HYPHEN,
    AKEY_SPACE,
    AKEY_ENTER,
    AKEY_BACKSPACE,
    AKEY_TAB,
    AKEY_PAGEUP,
    AKEY_PAGEDOWN,
    AKEY_END,
    AKEY_HOME,
    AKEY_INSERT,
    AKEY_DELETE,
    AKEY_ADD,
    AKEY_SUBTRACT,
    AKEY_MULTIPLY,
    AKEY_DIVIDE,
    AKEY_LEFT,
    AKEY_RIGHT,
    AKEY_UP,
    AKEY_DOWN,
    AKEY_NUMPAD0,
    AKEY_NUMPAD1,
    AKEY_NUMPAD2,
    AKEY_NUMPAD3,
    AKEY_NUMPAD4,
    AKEY_NUMPAD5,
    AKEY_NUMPAD6,
    AKEY_NUMPAD7,
    AKEY_NUMPAD8,
    AKEY_NUMPAD9,
    AKEY_F1,
    AKEY_F2,
    AKEY_F3,
    AKEY_F4,
    AKEY_F5,
    AKEY_F6,
    AKEY_F7,
    AKEY_F8,
    AKEY_F9,
    AKEY_F10,
    AKEY_F11,
    AKEY_F12,
    AKEY_F13,
    AKEY_F14,
    AKEY_F15,
    AKEY_PAUSE,
    AKEY_TILDE,
    AKEY_DASH,
    AKEY_RETURN,
    AKEY_QUOTE,
    ARIGHT_BUTTON,
    ALEFT_BUTTON
};

    /**
     * @enum Direction
     * @brief Enum for managing movement direction.
     * @details This enum is used in games where the player maintains a movement direction
     * across multiple frames (e.g., Pac-Man, Snake, etc.).
     * Each value is self-explanatory, so individual descriptions are omitted.
     * @see arcade::game::SnakeGame, arcade::game::PacmanGame
     */
    enum Direction { UP, DOWN, LEFT, RIGHT };


    /**
     * @enum ButtonState
     * @brief Enum for managing button states.
     * @details This enum is used to manage various button states. It was mainly designed
     * for future extensions and compatibility with the other group.
     * Each value is self-explanatory, so individual descriptions are omitted.
     */
    enum ButtonState { DISABLED, HOVER, PRESSED };


    /**
     * @enum EntityType
     * @brief Describes the nature of an entity.
     * @details This enum allows handling entities differently based on their nature.
     * Each value is self-explanatory, so individual descriptions are omitted.
     * @see arcade::game::SnakeGame, arcade::game::PacmanGame
     */
enum EntityType { EMPTY, WALL, PLAYER, FOOD, ENEMY, OBSTACLE, COLLECTIBLE };

    /**
     * @enum EntityDraw
     * @brief Describes the visual form of an entity.
     * @details Entities can have different shapes, which require different rendering functions.
     * This enum is used in most display libraries to determine which function should be called
     * to render a given entity.
     * Each value is self-explanatory, so individual descriptions are omitted.
     * @see arcade::display::SDLDisplayModule, arcade::display::SFMLDisplayModule
     */
    enum EntityDraw { NONE, RECTANGLE, CIRCLE, SPRITE, TEXT };


    /**
     * @struct Position
     * @brief Defines the position of entities.
     * @details Represents the tile-based position of an entity within the graphical window.
     * Each member is self-explanatory, so individual descriptions are omitted.
     */
struct Position {
    int x;
    int y;

    /**
     * @brief Equality operator.
     * @details Compares two Position objects based on their x and y values.
     * @param other The position to compare with.
     * @return true if both x and y are equal; false otherwise.
     */
    bool operator==(const Position &other) const
    {
        return x == other.x && y == other.y;
    }
};

    /**
     * @struct Sprite
     * @brief Structure that holds a sprite.
     * @details This structure stores sprite data, including a binary representation,
     * a unique key, and the size of the sprite in bytes.
     */
    struct Sprite {
        std::string key; ///< Unique key identifying the sprite.
        const unsigned char *assets = nullptr; ///< Binary data of the sprite.
        size_t length; ///< Size of the sprite data in bytes.

        /**
         * @brief Equality operator.
         * @details Compares two sprites based on their unique keys.
         * @param other The sprite to compare with.
         * @return true if the keys are equal; false otherwise.
         */
        bool operator==(const Sprite &other) const
        {
            return key == other.key;
        }
    };


/* entity structure to store game/display data */
    /**
     * @struct Entity
     * @brief Structure used to store and describe an entity.
     * @details This structure contains all the necessary data to represent and display any type
     * and nature of entity across all graphical libraries. It allows rendering functions to receive
     * a single unified object as input for displaying entities.
     */
    struct Entity {
        EntityType type; ///< Nature/type of the entity (player, wall, etc.).
        Position pos; ///< Position of the entity on the grid.
        char display_char; ///< ASCII character used for display (e.g., for terminal-based rendering).
        uint32_t color; ///< Color used for basic rendering (rectangles, circles).
        std::string str; ///< Optional text content for text-based entities.
        Sprite sprite; ///< Sprite used for graphical rendering.

        /**
         * @brief Equality operator.
         * @details Compares two entities based on all their meaningful attributes (excluding the sprite).
         * @param other The entity to compare with.
         * @return true if all compared attributes are equal; false otherwise.
         */
        bool operator==(const Entity &other) const
        {
            return type == other.type &&
                   pos == other.pos &&
                   display_char == other.display_char &&
                   color == other.color &&
                   str == other.str;
        }
    };

 /**
 * @struct Mouse
 * @brief Mouse input handling structure.
 * @details The mouse is treated as a special type of event, requiring both the
 * click type (left, right, etc.) and the position of the event.
 */
    struct Mouse {
        Position pos; ///< Position of the mouse event.
        InputEvent event; ///< Type of mouse event (click, scroll, etc.).
    };


    /**
     * @union color_u
     * @brief Represents a color as either a 32-bit integer or an array of 4 components (RGBA).
     *
     * @details This union allows accessing a color in two different ways:
     * - As a single 32-bit value (`color`)
     * - As four 8-bit components (`components`) representing Red, Green, Blue, and Alpha channels.
     *
     * Useful for low-level pixel manipulation or rendering.
     */
    typedef union color_u {
        uint32_t color;       ///< The color represented as a 32-bit integer (e.g., 0xRRGGBBAA).
        uint8_t components[4];///< The color represented as an array: [Red, Green, Blue, Alpha].
        } color_t;


    /**
     * @enum components_e
     * @brief Enum to index color components (Red, Green, Blue, Alpha) within color_t.components.
     * @details This enum adapts the component order based on system endianness.
     * It is intended to be used with the `components` array of the `color_t` union
     * to access individual color channels in a portable way.
     * @see color_t
     *
     * @note The component order differs between big-endian and little-endian systems:
     * - On big-endian: R = 0, G = 1, B = 2, A = 3
     * - On little-endian: A = 0, B = 1, G = 2, R = 3
     */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    enum components_e { R, G, B, A };
#else
    enum components_e { A, B, G, R };
#endif

};// namespace arcade::types

/**
 * @brief Custom hash function for arcade::types::Position.
 *
 * @details This specialization of `std::hash` allows using `arcade::types::Position`
 * as a key in `std::unordered_map` or other hash-based containers.
 * It combines the hash of the `x` and `y` components using a variant
 * of the [Boost hash combine](https://www.boost.org/doc/libs/1_55_0/doc/html/hash/reference.html#boost.hash_combine).
 *
 * @see arcade::types::Position
 */
namespace std {
    template<>
/**
 * @brief Hash specialization for arcade::types::Position.
 * @details Enables the use of Position objects as keys in hash-based containers
 * like std::unordered_map and std::unordered_set.
 *
 * The hash function combines the hashes of the x and y coordinates using the
 * Boost-style hash combining method to reduce collisions.
 *
 * @see arcade::types::Position
 */

    struct hash<arcade::types::Position> {
        size_t operator()(const arcade::types::Position &pos) const
        {
            std::size_t h1 = std::hash<uint32_t>{}(pos.x);
            std::size_t h2 = std::hash<uint32_t>{}(pos.y);

            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
        }
    };
};
