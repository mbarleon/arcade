/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** FunctionFactory
*/

#include "FunctionFactory.hpp"

template <typename T>
T arcade::factory::FunctionFactory::loadFunction(const void *handle, const std::string &name)
{
    dlerror();
    void *sym = dlsym(const_cast<void *>(handle), name.c_str());
    const char *error_str = dlerror();

    if (error_str)
        throw error::Error("No such function.", "Utils/FunctionFactory.cpp:14");
    return reinterpret_cast<T>(sym);
}
