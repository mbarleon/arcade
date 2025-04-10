/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** NCursesDisplayModule
*/

/**
 * @file NCursesDisplayModule.cpp
 * @brief NCurses Display Module.
 * @author mbarleon
 * @version 1.0
 * @date 2025-04-09
 *
 * @details
 * This file contains the ncurses display module.
 */

#include "NCursesDisplayModule.hpp"

extern "C" {
    arcade::display::IDisplayModule *create(void)
    {
        return new arcade::display::NCursesDisplayModule();
    }

    void destroy(arcade::display::IDisplayModule *display)
    {
        delete display;
    }

    arcade::types::LibType getType(void)
    {
        return arcade::types::DISPLAY;
    }

    const char *getName()
    {
        return "NCURSES";
    }
}

/**
 * @brief Transforming the ncurses events into arcade events.
 * @details This function transforms the ncurses events into arcade events.
 * @return An InputEvent containing the current event
 */
arcade::types::InputEvent arcade::display::NCursesDisplayModule::convertKeyPress(int key)
{
    switch (key) {
        case 'A': case 'a': return types::InputEvent::AKEY_A;
        case 'B': case 'b': return types::InputEvent::AKEY_B;
        case 'C': case 'c': return types::InputEvent::AKEY_C;
        case 'D': case 'd': return types::InputEvent::AKEY_D;
        case 'E': case 'e': return types::InputEvent::AKEY_E;
        case 'F': case 'f': return types::InputEvent::AKEY_F;
        case 'G': case 'g': return types::InputEvent::AKEY_G;
        case 'H': case 'h': return types::InputEvent::AKEY_H;
        case 'I': case 'i': return types::InputEvent::AKEY_I;
        case 'J': case 'j': return types::InputEvent::AKEY_J;
        case 'K': case 'k': return types::InputEvent::AKEY_K;
        case 'L': case 'l': return types::InputEvent::AKEY_L;
        case 'M': case 'm': return types::InputEvent::AKEY_M;
        case 'N': case 'n': return types::InputEvent::AKEY_N;
        case 'O': case 'o': return types::InputEvent::AKEY_O;
        case 'P': case 'p': return types::InputEvent::AKEY_P;
        case 'Q': case 'q': return types::InputEvent::AKEY_Q;
        case 'R': case 'r': return types::InputEvent::AKEY_R;
        case 'S': case 's': return types::InputEvent::AKEY_S;
        case 'T': case 't': return types::InputEvent::AKEY_T;
        case 'U': case 'u': return types::InputEvent::AKEY_U;
        case 'V': case 'v': return types::InputEvent::AKEY_V;
        case 'W': case 'w': return types::InputEvent::AKEY_W;
        case 'X': case 'x': return types::InputEvent::AKEY_X;
        case 'Y': case 'y': return types::InputEvent::AKEY_Y;
        case 'Z': case 'z': return types::InputEvent::AKEY_Z;
        case '0': return types::InputEvent::AKEY_NUM0;
        case '1': return types::InputEvent::AKEY_NUM1;
        case '2': return types::InputEvent::AKEY_NUM2;
        case '3': return types::InputEvent::AKEY_NUM3;
        case '4': return types::InputEvent::AKEY_NUM4;
        case '5': return types::InputEvent::AKEY_NUM5;
        case '6': return types::InputEvent::AKEY_NUM6;
        case '7': return types::InputEvent::AKEY_NUM7;
        case '8': return types::InputEvent::AKEY_NUM8;
        case '9': return types::InputEvent::AKEY_NUM9;
        case 27: return types::InputEvent::AKEY_ESCAPE;
        case KEY_LEFT: return types::InputEvent::AKEY_LEFT;
        case KEY_RIGHT: return types::InputEvent::AKEY_RIGHT;
        case KEY_UP: return types::InputEvent::AKEY_UP;
        case KEY_DOWN: return types::InputEvent::AKEY_DOWN;
        case KEY_HOME: return types::InputEvent::AKEY_HOME;
        case KEY_END: return types::InputEvent::AKEY_END;
        case KEY_PPAGE: return types::InputEvent::AKEY_PAGEUP;
        case KEY_NPAGE: return types::InputEvent::AKEY_PAGEDOWN;
        case KEY_IC: return types::InputEvent::AKEY_INSERT;
        case KEY_DC: return types::InputEvent::AKEY_DELETE;
        case KEY_F(1): return types::InputEvent::AKEY_F1;
        case KEY_F(2): return types::InputEvent::AKEY_F2;
        case KEY_F(3): return types::InputEvent::AKEY_F3;
        case KEY_F(4): return types::InputEvent::AKEY_F4;
        case KEY_F(5): return types::InputEvent::AKEY_F5;
        case KEY_F(6): return types::InputEvent::AKEY_F6;
        case KEY_F(7): return types::InputEvent::AKEY_F7;
        case KEY_F(8): return types::InputEvent::AKEY_F8;
        case KEY_F(9): return types::InputEvent::AKEY_F9;
        case KEY_F(10): return types::InputEvent::AKEY_F10;
        case KEY_F(11): return types::InputEvent::AKEY_F11;
        case KEY_F(12): return types::InputEvent::AKEY_F12;
        case '\n': return types::InputEvent::AKEY_ENTER;
        case '\t': return types::InputEvent::AKEY_TAB;
        case ' ': return types::InputEvent::AKEY_SPACE;
        case KEY_BACKSPACE: return types::InputEvent::AKEY_BACKSPACE;
        case '=': return types::InputEvent::AKEY_EQUAL;
        case '-': return types::InputEvent::AKEY_HYPHEN;
        case '`': return types::InputEvent::AKEY_GRAVE;
        case '[': return types::InputEvent::AKEY_LBRACKET;
        case ']': return types::InputEvent::AKEY_RBRACKET;
        case ';': return types::InputEvent::AKEY_SEMICOLON;
        case ',': return types::InputEvent::AKEY_COMMA;
        case '.': return types::InputEvent::AKEY_PERIOD;
        case '\'': return types::InputEvent::AKEY_APOSTROPHE;
        case '/': return types::InputEvent::AKEY_SLASH;
        case '\\': return types::InputEvent::AKEY_BACKSLASH;
        case '*': return types::InputEvent::AKEY_MULTIPLY;
        case '+': return types::InputEvent::AKEY_ADD;
        case KEY_ENTER: return types::InputEvent::AKEY_RETURN;
        default: return types::InputEvent::AKEY_UNKNOWN;
    }
}

/**
 * @brief Constructor for the NCursesDisplayModule class.
 * @details This function initialises the screen for the ncurses.
 * @return void
 */
arcade::display::NCursesDisplayModule::NCursesDisplayModule()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
}

/**
 * @brief Destructor for the NCursesDisplayModule class.
 * @details This function ends the screen for the ncurses.
 * @return void
 */
arcade::display::NCursesDisplayModule::~NCursesDisplayModule()
{
    endwin();
}

/**
 * @brief Drawing the entities.
 * @details This function draws the entities.
 * It uses display_char except for text where it uses str.
 * @return void
 */
void arcade::display::NCursesDisplayModule::draw(Entities entities)
{
    clear();
    for (auto &it : entities) {
        if (it.first == arcade::types::NONE)
            continue;
        for (auto &ti : it.second) {
            int x = ti.pos.x;
            int y = ti.pos.y;
            if (it.first == arcade::types::TEXT)
                mvaddstr(y, x, ti.str.c_str());
            else
                mvaddch(y, x, ti.display_char);
        }
    }
    refresh();
}

/**
 * @brief Getting the ncurses event.
 * @details This function gets and returns the current ncurses event.
 * @return A pair containing the position of the mouse if the event is a mouse click, and the key that was pressed.
 */
std::pair<arcade::types::Position, arcade::types::InputEvent> arcade::display::NCursesDisplayModule::event()
{
    std::pair<arcade::types::Position, arcade::types::InputEvent> result;
    result.first = {0, 0};
    result.second = arcade::types::AKEY_UNKNOWN;

    int ch = getch();
    if (ch == KEY_MOUSE) {
        MEVENT event;
        if (getmouse(&event) == OK) {
            result.first.x = event.x;
            result.first.y = event.y;
            result.second = arcade::types::ARIGHT_BUTTON;
            return result;
        }
    } else if (ch != ERR) {
        result.second = convertKeyPress(ch);
    }
    return result;
}
