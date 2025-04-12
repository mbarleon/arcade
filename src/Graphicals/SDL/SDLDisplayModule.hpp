/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SDLDisplayModule
*/

#ifndef SDLDISPLAYMODULE_HPP_
    #define SDLDISPLAYMODULE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Assets/font.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rwops.h>
#include <utility>
#include "ADisplayModule.hpp"
#include "../../Utils/Error.hpp"

/**
 * @file SDLDisplayModule.hpp
 * @brief Header file for SDL display module.
 * @author Noé CARABIN (CorpsB)
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This file declares all the methods and attributes related to SDL rendering.
 * It defines the SDLDisplayModule class, which handles window creation, rendering,
 * and entity display operations using SDL2.
 */
namespace arcade::display {
    /**
     * @class SDLDisplayModule
     * @brief SDL-based implementation of the ADisplayModule interface.
     * @details This class handles rendering and event processing using the SDL2 library.
     * It is responsible for drawing visual elements such as shapes, sprites, and text,
     * and for capturing input events to be passed back to the core logic.
     * The class uses SDL_Window and SDL_Renderer to manage the window and render context,
     * and also supports TTF font rendering via SDL_ttf.
     *
     * @see ADisplayModule
     */
    class SDLDisplayModule : public ADisplayModule {
        public:
            SDLDisplayModule();
            ~SDLDisplayModule();

            void draw(Entities entities) override;
            std::pair<types::Position, types::InputEvent> event() override;

        private:
            void drawCircle(int baseX, int baseY);
            types::InputEvent mapSDLKeyToInputEvent(SDL_Keycode key);

            TTF_Font *_font;
            SDL_Window* _window;
            SDL_Renderer* _renderer;
            SDL_Event _event;
            bool _quit = false;
    };
}

#endif /* !SDLDISPLAYMODULE_HPP_ */
