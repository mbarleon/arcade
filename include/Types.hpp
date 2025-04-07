/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Types.hpp
*/

#pragma once

#include <cstdint>
#include <functional>

namespace arcade::types {
enum LibType {
    MENU,
    GAME,
    DISPLAY
};

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

enum Direction { UP, DOWN, LEFT, RIGHT };

enum ButtonState { DISABLED, HOVER, PRESSED };

enum EntityType { EMPTY, WALL, PLAYER, FOOD, ENEMY, OBSTACLE, COLLECTIBLE };
enum EntityDraw { NONE, RECTANGLE, CIRCLE, SPRITE };

/* position vector2u */
struct Position {
    int x;
    int y;

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
namespace std {
    template<>
    struct hash<arcade::types::Position> {
        size_t operator()(const arcade::types::Position &pos) const
        {
            return std::hash<uint32_t>()(pos.x) ^ (std::hash<uint32_t>()(pos.y) << 1);
        }
    };
};
