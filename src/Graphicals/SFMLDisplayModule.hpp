/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SFMLDisplayModule
*/

#ifndef SFMLDISPLAYMODULE_HPP_
    #define SFMLDISPLAYMODULE_HPP_
    #include "ADisplayModule.hpp"
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>

namespace arcade::display {
    class SFMLDisplayModule : public ADisplayModule {
        public:
            SFMLDisplayModule();
            ~SFMLDisplayModule() override;

            void draw(Entities entities) override;
            std::pair<types::Position, types::InputEvent> event() override;

        private:
            sf::RenderWindow _win;
            sf::Event _event;
            sf::Vector2i _mouse;
    };
};

#endif /* !SFMLDISPLAYMODULE_HPP_ */
