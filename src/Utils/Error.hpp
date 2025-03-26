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

/*
* generic Error class
*
* example:
*  - throw exception::Error("arcade::Core", "failed to open ", <path>, " because: ", dlerror());
*/
namespace arcade::exception {
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
