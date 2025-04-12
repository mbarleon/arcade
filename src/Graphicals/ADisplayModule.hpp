/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** ADisplayModule
*/

#ifndef ADISPLAYMODULE_HPP_
    #define ADISPLAYMODULE_HPP_
    #include "IDisplayModule.hpp"

/**
 * @file ADisplayModule.hpp
 * @brief Declares the abstract base class for display modules in the Arcade project.
 * @author Jason Koenig and Noé Carabin (CorpsB)
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This file defines the ADisplayModule class, which provides a default implementation
 * of the IDisplayModule interface. It is intended to serve as a common base for
 * display modules using various graphical libraries such as SDL or SFML.
 * ADisplayModule implements the main draw and event methods, while derived classes
 * are expected to implement specific rendering behavior.
 *
 * @see arcade::display::IDisplayModule
 */


namespace arcade::display {
    /**
     * @class ADisplayModule
     * @brief Abstract base class for graphical display modules.
     * @details ADisplayModule provides a partial implementation of the IDisplayModule interface.
     * It is used as a base class for rendering backends like SDL, SFML, or others.
     * Derived classes are responsible for defining the graphical behavior in detail.
     * This class simplifies the implementation of new display modules by
     * centralizing common logic related to event handling and rendering.
     *
     * @see IDisplayModule
     */
    class ADisplayModule : public IDisplayModule {
        public:
            ADisplayModule();
            virtual ~ADisplayModule();

            void draw(Entities entities) override;
            std::pair<types::Position, types::InputEvent> event() override;
    };
};

#endif /* !ADISPLAYMODULE_HPP_ */
