/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SDLDisplayModule
*/

#include "SDLDisplayModule.hpp"
#include "../Utils/Error.hpp"

arcade::display::SDLDisplayModule::SDLDisplayModule()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw arcade::exception::Error("SDL Constructor : Line 14", "ERROR - INITIALISATION FAILED");
    this->_window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        VIDEO_SIZE.first, VIDEO_SIZE.second, SDL_WINDOW_SHOWN);
    if (!this->_window)
        throw arcade::exception::Error("SDL Constructor : Line 18", "ERROR - WINDOW INITIALISATION FAILED");
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->_renderer)
        throw arcade::exception::Error("SDL Constructor : Line 21", "ERROR - RENDERER INITIALISATION FAILED");
}

void arcade::display::SDLDisplayModule::draw(Entities entities)
{
    for ( auto &it : entities) {
        if (it.first == arcade::types::NONE)
            continue;
        for( auto &ti : it.second) {
            arcade::types::color_t color;
            color.color = ti.color;

            SDL_SetRenderDrawColor(this->_renderer, color.components[0],
                color.components[1], color.components[2], color.components[3]);

            if (it.first == arcade::types::RECTANGLE) {
                SDL_Rect rect = {ti.pos.x, ti.pos.y, RECTANGLE_SIZE, RECTANGLE_SIZE};
                SDL_RenderFillRect(this->_renderer, &rect);
                continue;
            }

            if (it.first == arcade::types::CIRCLE) {
                throw arcade::exception::Error("SDL CAN'T DISPLAY CIRCLE : Line 34");
                continue;
            }

            if (it.first == arcade::types::SPRITE) {
                continue;
            }
        }
    }
}

std::pair<arcade::types::Position, arcade::types::InputEvent> arcade::display::SDLDisplayModule::event()
{
    std::pair<arcade::types::Position, arcade::types::InputEvent> result;
    result.second = arcade::types::KEY_UNKNOWN;

    while(SDL_PollEvent(&this->_event)) {
        arcade::types::Position pos;
        pos.x = 0;
        pos.y = 0;

        if (this->_event.type == SDL_QUIT)
            return {pos, arcade::types::KEY_ESCAPE};
        if (this->_event.type == SDL_MOUSEBUTTONDOWN) {
            pos.x = this->_event.button.x;
            pos.y = this->_event.button.y;
            result = {pos, arcade::types::RIGHT_BUTTON};
            continue;
        }
        if (this->_event.type == SDL_KEYDOWN)
            result = {pos, mapSDLKeyToInputEvent(this->_event.key.keysym.sym)};
    }
    return result;
}

arcade::display::SDLDisplayModule::~SDLDisplayModule()
{
    if (this->_renderer)
        SDL_DestroyRenderer(this->_renderer);
    if (this->_window)
        SDL_DestroyWindow(this->_window);
    SDL_Quit();
}

arcade::types::InputEvent mapSDLKeyToInputEvent(SDL_Keycode key)
{
    switch (key) {
        case SDLK_a: return arcade::types::KEY_A;
        case SDLK_b: return arcade::types::KEY_B;
        case SDLK_c: return arcade::types::KEY_C;
        case SDLK_d: return arcade::types::KEY_D;
        case SDLK_e: return arcade::types::KEY_E;
        case SDLK_f: return arcade::types::KEY_F;
        case SDLK_g: return arcade::types::KEY_G;
        case SDLK_h: return arcade::types::KEY_H;
        case SDLK_i: return arcade::types::KEY_I;
        case SDLK_j: return arcade::types::KEY_J;
        case SDLK_k: return arcade::types::KEY_K;
        case SDLK_l: return arcade::types::KEY_L;
        case SDLK_m: return arcade::types::KEY_M;
        case SDLK_n: return arcade::types::KEY_N;
        case SDLK_o: return arcade::types::KEY_O;
        case SDLK_p: return arcade::types::KEY_P;
        case SDLK_q: return arcade::types::KEY_Q;
        case SDLK_r: return arcade::types::KEY_R;
        case SDLK_s: return arcade::types::KEY_S;
        case SDLK_t: return arcade::types::KEY_T;
        case SDLK_u: return arcade::types::KEY_U;
        case SDLK_v: return arcade::types::KEY_V;
        case SDLK_w: return arcade::types::KEY_W;
        case SDLK_x: return arcade::types::KEY_X;
        case SDLK_y: return arcade::types::KEY_Y;
        case SDLK_z: return arcade::types::KEY_Z;

        case SDLK_0: return arcade::types::KEY_NUM0;
        case SDLK_1: return arcade::types::KEY_NUM1;
        case SDLK_2: return arcade::types::KEY_NUM2;
        case SDLK_3: return arcade::types::KEY_NUM3;
        case SDLK_4: return arcade::types::KEY_NUM4;
        case SDLK_5: return arcade::types::KEY_NUM5;
        case SDLK_6: return arcade::types::KEY_NUM6;
        case SDLK_7: return arcade::types::KEY_NUM7;
        case SDLK_8: return arcade::types::KEY_NUM8;
        case SDLK_9: return arcade::types::KEY_NUM9;

        case SDLK_ESCAPE: return arcade::types::KEY_ESCAPE;
        case SDLK_LCTRL: return arcade::types::KEY_LCONTROL;
        case SDLK_LSHIFT: return arcade::types::KEY_LSHIFT;
        case SDLK_LALT: return arcade::types::KEY_LALT;
        case SDLK_RCTRL: return arcade::types::KEY_RCONTROL;
        case SDLK_RSHIFT: return arcade::types::KEY_RSHIFT;
        case SDLK_RALT: return arcade::types::KEY_RALT;

        case SDLK_SPACE: return arcade::types::KEY_SPACE;
        case SDLK_RETURN: return arcade::types::KEY_ENTER;
        case SDLK_BACKSPACE: return arcade::types::KEY_BACKSPACE;
        case SDLK_TAB: return arcade::types::KEY_TAB;

        case SDLK_LEFT: return arcade::types::KEY_LEFT;
        case SDLK_RIGHT: return arcade::types::KEY_RIGHT;
        case SDLK_UP: return arcade::types::KEY_UP;
        case SDLK_DOWN: return arcade::types::KEY_DOWN;

        case SDLK_F1: return arcade::types::KEY_F1;
        case SDLK_F2: return arcade::types::KEY_F2;
        case SDLK_F3: return arcade::types::KEY_F3;
        case SDLK_F4: return arcade::types::KEY_F4;
        case SDLK_F5: return arcade::types::KEY_F5;
        case SDLK_F6: return arcade::types::KEY_F6;
        case SDLK_F7: return arcade::types::KEY_F7;
        case SDLK_F8: return arcade::types::KEY_F8;
        case SDLK_F9: return arcade::types::KEY_F9;
        case SDLK_F10: return arcade::types::KEY_F10;
        case SDLK_F11: return arcade::types::KEY_F11;
        case SDLK_F12: return arcade::types::KEY_F12;
        case SDLK_F13: return arcade::types::KEY_F13;
        case SDLK_F14: return arcade::types::KEY_F14;
        case SDLK_F15: return arcade::types::KEY_F15;
        case SDLK_PAUSE: return arcade::types::KEY_PAUSE;

        case SDLK_BACKQUOTE: return arcade::types::KEY_TILDE;
        case SDLK_MINUS: return arcade::types::KEY_DASH;
        case SDLK_QUOTE: return arcade::types::KEY_QUOTE;

        case SDLK_LEFTBRACKET: return arcade::types::KEY_LBRACKET;
        case SDLK_RIGHTBRACKET: return arcade::types::KEY_RBRACKET;
        case SDLK_SEMICOLON: return arcade::types::KEY_SEMICOLON;
        case SDLK_COMMA: return arcade::types::KEY_COMMA;
        case SDLK_PERIOD: return arcade::types::KEY_PERIOD;
        case SDLK_SLASH: return arcade::types::KEY_SLASH;
        case SDLK_BACKSLASH: return arcade::types::KEY_BACKSLASH;
        case SDLK_EQUALS: return arcade::types::KEY_EQUAL;

        case SDLK_PAGEDOWN: return arcade::types::KEY_PAGEDOWN;
        case SDLK_PAGEUP: return arcade::types::KEY_PAGEUP;
        case SDLK_END: return arcade::types::KEY_END;
        case SDLK_HOME: return arcade::types::KEY_HOME;
        case SDLK_INSERT: return arcade::types::KEY_INSERT;
        case SDLK_DELETE: return arcade::types::KEY_DELETE;

        case SDLK_KP_0: return arcade::types::KEY_NUMPAD0;
        case SDLK_KP_1: return arcade::types::KEY_NUMPAD1;
        case SDLK_KP_2: return arcade::types::KEY_NUMPAD2;
        case SDLK_KP_3: return arcade::types::KEY_NUMPAD3;
        case SDLK_KP_4: return arcade::types::KEY_NUMPAD4;
        case SDLK_KP_5: return arcade::types::KEY_NUMPAD5;
        case SDLK_KP_6: return arcade::types::KEY_NUMPAD6;
        case SDLK_KP_7: return arcade::types::KEY_NUMPAD7;
        case SDLK_KP_8: return arcade::types::KEY_NUMPAD8;
        case SDLK_KP_9: return arcade::types::KEY_NUMPAD9;

        case SDLK_KP_PLUS: return arcade::types::KEY_ADD;
        case SDLK_KP_MINUS: return arcade::types::KEY_SUBTRACT;
        case SDLK_KP_MULTIPLY: return arcade::types::KEY_MULTIPLY;
        case SDLK_KP_DIVIDE: return arcade::types::KEY_DIVIDE;

        case SDLK_MENU: return arcade::types::KEY_MENU;

        default:
            return arcade::types::KEY_UNKNOWN;
    }
}