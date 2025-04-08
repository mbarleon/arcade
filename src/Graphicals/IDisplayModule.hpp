/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IDisplayModule.hpp
*/

#pragma once

#include "../../include/Types.hpp"
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @file IDisplayModule.hpp
 * @brief Declaration of the graphical display interface.
 * @author Shared with the partner group
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This class defines the interface that all graphical modules must implement
 * to be compatible with the Arcade platform.
 * It includes the required functions for rendering the game, handling user input,
 * and managing the display lifecycle.
 */

namespace arcade::display {
    /**
     * @class IDisplayModule
     * @brief Interface for all Arcade-compatible games.
     *
     * @details
     * This class defines the interface that every game must implement
     * to be compatible with the Arcade platform.
     * It includes all the required methods for initializing the game, updating its logic,
     * and retrieving its state and score.
     */
    class IDisplayModule {
        public:
            static constexpr const char *DEFAULT_FONT_PATH = "./assets/font.ttf";
            static constexpr std::pair VIDEO_SIZE = {600, 800};
            static constexpr float CIRCLE_RADIUS = 10.0f;
            static constexpr float RECTANGLE_SIZE = 20.0f;
            static constexpr float TEXT_SIZE = 20.0f;

            using Entities = std::unordered_map<types::EntityDraw, std::vector<types::Entity>>;

            virtual ~IDisplayModule() = default;

            virtual void draw(Entities entities) = 0;
            virtual std::pair<types::Position, types::InputEvent> event() = 0;
    };
};// namespace arcade::display
