/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SFMLDisplayModule
*/

#ifndef SFMLDISPLAYMODULE_HPP_
    #define SFMLDISPLAYMODULE_HPP_
    #include "../ADisplayModule.hpp"
    #include "SFMLCharTraitFix.hpp"
    #include "../Assets/font.hpp"
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>

/**
 * @file SFMLDisplayModule.hpp
 * @brief Header file for SFML display module.
 * @author Jason KOENIG
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Declares all the methods and attributes related to SFML rendering.
 * It defines the SFMLDisplayModule class, which handles window creation, rendering,
 * and entity display operations using the SFML library.
 */
namespace arcade::display {
    /**
     * @class SFMLDisplayModule
     * @brief SFML-based implementation of the ADisplayModule interface.
     * @details This class handles rendering and event processing using the SFML library.
     * It is responsible for drawing visual elements such as shapes, sprites, and text,
     * and for capturing input events to be passed back to the core logic.
     *
     * @see ADisplayModule
     */
    class SFMLDisplayModule : public ADisplayModule {
        public:
            SFMLDisplayModule();
            ~SFMLDisplayModule() override = default;

            void draw(Entities entities) override;
            std::pair<types::Position, types::InputEvent> event() override;

        private:
            sf::RenderWindow _win;
            sf::Event _event;
            sf::Vector2i _mouse;
            sf::RectangleShape _pixel;
            sf::CircleShape _circle;
            sf::Font _font;
            std::unordered_map<std::string, std::pair<sf::Texture, sf::Sprite>> _sprites;
            std::unordered_map<std::string, sf::Text> _textes;
    };
};

#endif /* !SFMLDISPLAYMODULE_HPP_ */
