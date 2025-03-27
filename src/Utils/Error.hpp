/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Error
*/

#pragma once

#include <exception>
#include <sstream>
#include <string>

/**
 * @file Error.hpp
 * @brief Declaration of the program's custom exception class.
 * @author Shared with the partner group
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This file contains the declaration of the Error class created for the Arcade project.
 * It inherits from the standard std::exception class and provides a custom error message mechanism.
 */

namespace arcade::exception {
    /**
     * @class Error
     * @brief Custom exception class.
     *
     * @details
     * This error class inherits from std::exception. It allows the program to be cleanly
     * interrupted when problems are detected, while providing a clear error message.
     */
    class Error : public std::exception {
        public:
            template<typename... Args>
            Error(const std::string &where, Args &&...args)
                : _where(where), _what(concatStrings(std::forward<Args>(args)...))
            {
                /* empty */
            }

            const char *what() const noexcept override;
            const char *where() const noexcept;

        private:
            const std::string _where;
            const std::string _what;

            template<typename... Args>
            static std::string concatStrings(Args &&...args)
            {
                std::ostringstream oss;

                (oss << ... << args);
                return oss.str();
            }
    };
};// namespace arcade::exception
