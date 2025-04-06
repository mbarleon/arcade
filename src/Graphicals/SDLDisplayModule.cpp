/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SDLDisplayModule
*/

#include "SDLDisplayModule.hpp"
#include "../Utils/Error.hpp"

extern "C" {
    arcade::display::IDisplayModule *create(void)
    {
        return new arcade::display::SDLDisplayModule();
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
        return "SDL2";
    }
}

arcade::display::SDLDisplayModule::SDLDisplayModule()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw arcade::exception::Error("SDL Constructor : Line 14", "ERROR - INITIALISATION FAILED");
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        VIDEO_SIZE.first, VIDEO_SIZE.second, SDL_WINDOW_SHOWN);
    if (!_window)
        throw arcade::exception::Error("SDL Constructor : Line 18", "ERROR - WINDOW INITIALISATION FAILED");
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer)
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

            SDL_SetRenderDrawColor(_renderer, color.components[0],
                color.components[1], color.components[2], color.components[3]);

            if (it.first == arcade::types::RECTANGLE) {
                SDL_Rect rect = {ti.pos.x, ti.pos.y, RECTANGLE_SIZE, RECTANGLE_SIZE};
                SDL_RenderFillRect(_renderer, &rect);
                continue;
            }

            if (it.first == arcade::types::CIRCLE) {
                drawCircle(ti.pos.x, ti.pos.y);
                continue;
            }

            if (it.first == arcade::types::SPRITE) {
                continue;
            }
        }
    }
}

void arcade::display::SDLDisplayModule::drawCircle(int baseX, int baseY)
{
    const int centerX = baseX + CIRCLE_RADIUS;
    const int centerY = baseY + CIRCLE_RADIUS;

    for (int dy = -CIRCLE_RADIUS; dy <= CIRCLE_RADIUS; dy++) {
        int dx = (int)sqrt(CIRCLE_RADIUS * CIRCLE_RADIUS - dy * dy);
        SDL_RenderDrawLine(_renderer, centerX - dx, centerY + dy, centerX + dx, centerY + dy);
    }
}

std::pair<arcade::types::Position, arcade::types::InputEvent> arcade::display::SDLDisplayModule::event()
{
    std::pair<arcade::types::Position, arcade::types::InputEvent> result;
    result.second = arcade::types::AKEY_UNKNOWN;

    if (_quit) {
        result = {{0, 0}, arcade::types::AKEY_ESCAPE};
        return result;
    }

    while(SDL_PollEvent(&_event)) {
        arcade::types::Position pos;
        pos.x = 0;
        pos.y = 0;

        if (_event.type == SDL_QUIT) {
            _quit = true;
            return {pos, arcade::types::AKEY_ESCAPE};
        }
        if (_event.type == SDL_MOUSEBUTTONDOWN) {
            pos.x = _event.button.x;
            pos.y = _event.button.y;
            result = {pos, arcade::types::ARIGHT_BUTTON};
            continue;
        }
        if (_event.type == SDL_KEYDOWN)
            result = {pos, mapSDLKeyToInputEvent(_event.key.keysym.sym)};
    }
    return result;
}

arcade::display::SDLDisplayModule::~SDLDisplayModule()
{
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
    SDL_Quit();
}

arcade::types::InputEvent mapSDLKeyToInputEvent(SDL_Keycode key)
{
    switch (key) {
        case SDLK_a: return arcade::types::AKEY_A;
        case SDLK_b: return arcade::types::AKEY_B;
        case SDLK_c: return arcade::types::AKEY_C;
        case SDLK_d: return arcade::types::AKEY_D;
        case SDLK_e: return arcade::types::AKEY_E;
        case SDLK_f: return arcade::types::AKEY_F;
        case SDLK_g: return arcade::types::AKEY_G;
        case SDLK_h: return arcade::types::AKEY_H;
        case SDLK_i: return arcade::types::AKEY_I;
        case SDLK_j: return arcade::types::AKEY_J;
        case SDLK_k: return arcade::types::AKEY_K;
        case SDLK_l: return arcade::types::AKEY_L;
        case SDLK_m: return arcade::types::AKEY_M;
        case SDLK_n: return arcade::types::AKEY_N;
        case SDLK_o: return arcade::types::AKEY_O;
        case SDLK_p: return arcade::types::AKEY_P;
        case SDLK_q: return arcade::types::AKEY_Q;
        case SDLK_r: return arcade::types::AKEY_R;
        case SDLK_s: return arcade::types::AKEY_S;
        case SDLK_t: return arcade::types::AKEY_T;
        case SDLK_u: return arcade::types::AKEY_U;
        case SDLK_v: return arcade::types::AKEY_V;
        case SDLK_w: return arcade::types::AKEY_W;
        case SDLK_x: return arcade::types::AKEY_X;
        case SDLK_y: return arcade::types::AKEY_Y;
        case SDLK_z: return arcade::types::AKEY_Z;

        case SDLK_0: return arcade::types::AKEY_NUM0;
        case SDLK_1: return arcade::types::AKEY_NUM1;
        case SDLK_2: return arcade::types::AKEY_NUM2;
        case SDLK_3: return arcade::types::AKEY_NUM3;
        case SDLK_4: return arcade::types::AKEY_NUM4;
        case SDLK_5: return arcade::types::AKEY_NUM5;
        case SDLK_6: return arcade::types::AKEY_NUM6;
        case SDLK_7: return arcade::types::AKEY_NUM7;
        case SDLK_8: return arcade::types::AKEY_NUM8;
        case SDLK_9: return arcade::types::AKEY_NUM9;

        case SDLK_ESCAPE: return arcade::types::AKEY_ESCAPE;
        case SDLK_LCTRL: return arcade::types::AKEY_LCONTROL;
        case SDLK_LSHIFT: return arcade::types::AKEY_LSHIFT;
        case SDLK_LALT: return arcade::types::AKEY_LALT;
        case SDLK_RCTRL: return arcade::types::AKEY_RCONTROL;
        case SDLK_RSHIFT: return arcade::types::AKEY_RSHIFT;
        case SDLK_RALT: return arcade::types::AKEY_RALT;

        case SDLK_SPACE: return arcade::types::AKEY_SPACE;
        case SDLK_RETURN: return arcade::types::AKEY_ENTER;
        case SDLK_BACKSPACE: return arcade::types::AKEY_BACKSPACE;
        case SDLK_TAB: return arcade::types::AKEY_TAB;

        case SDLK_LEFT: return arcade::types::AKEY_LEFT;
        case SDLK_RIGHT: return arcade::types::AKEY_RIGHT;
        case SDLK_UP: return arcade::types::AKEY_UP;
        case SDLK_DOWN: return arcade::types::AKEY_DOWN;

        case SDLK_F1: return arcade::types::AKEY_F1;
        case SDLK_F2: return arcade::types::AKEY_F2;
        case SDLK_F3: return arcade::types::AKEY_F3;
        case SDLK_F4: return arcade::types::AKEY_F4;
        case SDLK_F5: return arcade::types::AKEY_F5;
        case SDLK_F6: return arcade::types::AKEY_F6;
        case SDLK_F7: return arcade::types::AKEY_F7;
        case SDLK_F8: return arcade::types::AKEY_F8;
        case SDLK_F9: return arcade::types::AKEY_F9;
        case SDLK_F10: return arcade::types::AKEY_F10;
        case SDLK_F11: return arcade::types::AKEY_F11;
        case SDLK_F12: return arcade::types::AKEY_F12;
        case SDLK_F13: return arcade::types::AKEY_F13;
        case SDLK_F14: return arcade::types::AKEY_F14;
        case SDLK_F15: return arcade::types::AKEY_F15;
        case SDLK_PAUSE: return arcade::types::AKEY_PAUSE;

        case SDLK_BACKQUOTE: return arcade::types::AKEY_TILDE;
        case SDLK_MINUS: return arcade::types::AKEY_DASH;
        case SDLK_QUOTE: return arcade::types::AKEY_QUOTE;

        case SDLK_LEFTBRACKET: return arcade::types::AKEY_LBRACKET;
        case SDLK_RIGHTBRACKET: return arcade::types::AKEY_RBRACKET;
        case SDLK_SEMICOLON: return arcade::types::AKEY_SEMICOLON;
        case SDLK_COMMA: return arcade::types::AKEY_COMMA;
        case SDLK_PERIOD: return arcade::types::AKEY_PERIOD;
        case SDLK_SLASH: return arcade::types::AKEY_SLASH;
        case SDLK_BACKSLASH: return arcade::types::AKEY_BACKSLASH;
        case SDLK_EQUALS: return arcade::types::AKEY_EQUAL;

        case SDLK_PAGEDOWN: return arcade::types::AKEY_PAGEDOWN;
        case SDLK_PAGEUP: return arcade::types::AKEY_PAGEUP;
        case SDLK_END: return arcade::types::AKEY_END;
        case SDLK_HOME: return arcade::types::AKEY_HOME;
        case SDLK_INSERT: return arcade::types::AKEY_INSERT;
        case SDLK_DELETE: return arcade::types::AKEY_DELETE;

        case SDLK_KP_0: return arcade::types::AKEY_NUMPAD0;
        case SDLK_KP_1: return arcade::types::AKEY_NUMPAD1;
        case SDLK_KP_2: return arcade::types::AKEY_NUMPAD2;
        case SDLK_KP_3: return arcade::types::AKEY_NUMPAD3;
        case SDLK_KP_4: return arcade::types::AKEY_NUMPAD4;
        case SDLK_KP_5: return arcade::types::AKEY_NUMPAD5;
        case SDLK_KP_6: return arcade::types::AKEY_NUMPAD6;
        case SDLK_KP_7: return arcade::types::AKEY_NUMPAD7;
        case SDLK_KP_8: return arcade::types::AKEY_NUMPAD8;
        case SDLK_KP_9: return arcade::types::AKEY_NUMPAD9;

        case SDLK_KP_PLUS: return arcade::types::AKEY_ADD;
        case SDLK_KP_MINUS: return arcade::types::AKEY_SUBTRACT;
        case SDLK_KP_MULTIPLY: return arcade::types::AKEY_MULTIPLY;
        case SDLK_KP_DIVIDE: return arcade::types::AKEY_DIVIDE;

        case SDLK_MENU: return arcade::types::AKEY_MENU;

        default:
            return arcade::types::AKEY_UNKNOWN;
    }
}
