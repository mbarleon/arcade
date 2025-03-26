/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Types.hpp
*/

#pragma once

#include <cstdint>
#include <functional>

// clang-format off
namespace arcade::types {
enum LibType {
    MENU,
    GAME,
    DISPLAY
};

enum InputEvent {
    KEY_UNKNOWN = -1,
    KEY_A = 0,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_NUM0,
    KEY_NUM1,
    KEY_NUM2,
    KEY_NUM3,
    KEY_NUM4,
    KEY_NUM5,
    KEY_NUM6,
    KEY_NUM7,
    KEY_NUM8,
    KEY_NUM9,
    KEY_ESCAPE,
    KEY_LCONTROL,
    KEY_LSHIFT,
    KEY_LALT,
    KEY_LSYSTEM,
    KEY_RCONTROL,
    KEY_RSHIFT,
    KEY_RALT,
    KEY_RSYSTEM,
    KEY_MENU,
    KEY_LBRACKET,
    KEY_RBRACKET,
    KEY_SEMICOLON,
    KEY_COMMA,
    KEY_PERIOD,
    KEY_APOSTROPHE,
    KEY_SLASH,
    KEY_BACKSLASH,
    KEY_GRAVE,
    KEY_EQUAL,
    KEY_HYPHEN,
    KEY_SPACE,
    KEY_ENTER,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_PAGEUP,
    KEY_PAGEDOWN,
    KEY_END,
    KEY_HOME,
    KEY_INSERT,
    KEY_DELETE,
    KEY_ADD,
    KEY_SUBTRACT,
    KEY_MULTIPLY,
    KEY_DIVIDE,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
    KEY_NUMPAD0,
    KEY_NUMPAD1,
    KEY_NUMPAD2,
    KEY_NUMPAD3,
    KEY_NUMPAD4,
    KEY_NUMPAD5,
    KEY_NUMPAD6,
    KEY_NUMPAD7,
    KEY_NUMPAD8,
    KEY_NUMPAD9,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_PAUSE,
    KEY_TILDE,
    KEY_DASH,
    KEY_RETURN,
    KEY_QUOTE,
    RIGHT_BUTTON,
    LEFT_BUTTON
};

enum Direction { UP, DOWN, LEFT, RIGHT };

enum ButtonState { DISABLED, HOVER, PRESSED };

enum EntityType { EMPTY, WALL, PLAYER, FOOD, ENEMY, OBSTACLE, COLLECTIBLE };
enum EntityDraw { NONE, RECTANGLE, CIRCLE, SPRITE };

/* position vector2u */
struct Position {
    uint32_t x;
    uint32_t y;

    /* overload operator == to compare (pos == other.pos) */
    bool operator==(const Position &other) const
    {
        return x == other.x && y == other.y;
    }
};

/* entity structure to store game/display data */
struct Entity {
    EntityType type;
    Position pos;
    char display_char;
    uint32_t color;
};

/* mouse structure to store pos/event */
struct Mouse {
    Position pos;
    InputEvent event;
};

/*
* INFO:
* Allows to 'split' the colors into 4 uint8_t
*/
typedef union color_u {
    uint32_t color;
    uint8_t components[4];
} color_t;

/*
* INFO:
* To be used with color_t.components to access the correct component
*/
enum components_e { R, G, B, A };

};// namespace arcade::types

/*
* simple types::Position hash for unordered_map
*/
template<>
struct std::hash<arcade::types::Position> {
    size_t operator()(const arcade::types::Position &pos) const
    {
        return std::hash<uint32_t>()(pos.x) ^ (std::hash<uint32_t>()(pos.y) << 1);
    }
};
// clang-format on
