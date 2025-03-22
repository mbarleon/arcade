/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Error
*/

#pragma once

#include <string>
#include <exception>

namespace arcade::error {
    class Error: public std::exception {
        public:
            Error(const std::string what, const std::string where):
                _what(what), _where(where) {}

            const char *where(void) const noexcept;
            const char *what(void) const noexcept override;
        private:
            const std::string _what;
            const std::string _where;
    };
};
