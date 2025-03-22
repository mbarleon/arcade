/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** FunctionFactory
*/

#pragma once

#include <string>
#include <dlfcn.h>
#include "Error.hpp"

namespace arcade::factory {
    class FunctionFactory {
        public:
        FunctionFactory() = default;
        ~FunctionFactory() = default;

        template <typename T>
        static T loadFunction(const void *handle, const std::string &name);

        static void *openLib(const std::string &path);
        static void closeLib(void *handle);
    };
};
