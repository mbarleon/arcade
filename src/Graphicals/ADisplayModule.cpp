/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** ADisplayModule
*/

#include "ADisplayModule.hpp"

/**
 * @file ADisplayModule.cpp
 * @brief Provides default constructor and destructor implementations for ADisplayModule.
 * @author ...
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This source file contains the default implementations of the ADisplayModule class.
 * It exists primarily to separate the interface from implementation, even if the methods are trivial.
 *
 * The class serves as a base for all display modules in the Arcade project, such as SDL and SFML.
 *
 * @see ADisplayModule.hpp
 */

arcade::display::ADisplayModule::ADisplayModule() = default;

arcade::display::ADisplayModule::~ADisplayModule() = default;

/**
 * @brief Rendering function.
 * @details This function takes a list of entities and displays them one by one
 * in the graphical window.
 * @param entities The list of entities to render on screen.
 */
void arcade::display::ADisplayModule::draw(__attribute__((unused)) Entities entities)
{
}

/**
 * @brief Returns the last triggered event.
 * @details This function provides the most recent input event along with the associated position.
 * In this base implementation, it returns a default (empty) pair.
 * @return A pair containing the position and the triggered input event.
 */
std::pair<arcade::types::Position, arcade::types::InputEvent> arcade::display::ADisplayModule::event()
{
    return std::pair<types::Position, types::InputEvent>();
}
