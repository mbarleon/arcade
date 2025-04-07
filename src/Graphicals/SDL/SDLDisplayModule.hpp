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
#include <utility>
#include "ADisplayModule.hpp"
#include "../../Utils/Error.hpp"

namespace arcade::display {
    class SDLDisplayModule : public ADisplayModule {
        public:
            SDLDisplayModule();
            ~SDLDisplayModule();

            void draw(Entities entities) override;
            std::pair<types::Position, types::InputEvent> event() override;

        private:
            void drawCircle(int baseX, int baseY);
            types::InputEvent mapSDLKeyToInputEvent(SDL_Keycode key);

            SDL_Window* _window;
            SDL_Renderer* _renderer;
            SDL_Event _event;
            bool _quit = false;
    };
}

#endif /* !SDLDISPLAYMODULE_HPP_ */
