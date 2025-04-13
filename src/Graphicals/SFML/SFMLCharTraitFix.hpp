/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** SFMLCharTraitFix
*/

#pragma once
#include <SFML/Config.hpp>
#include <string>
#include <cstring>
#include <cwchar>

/**
 * @file SFMLCharTraitFix.cpp
 * @brief Contains compatibilty functions related to SFML.
 * @author Mathieu BARLEON
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Includes patches that correct SFML errors to ensure compatibility
 * with certain operating systems.
 */
namespace std {
    template<>
    struct char_traits<sf::Uint32> {
        using char_type = sf::Uint32;
        using int_type = std::uint32_t;
        using off_type = std::streamoff;
        using pos_type = std::streampos;
        using state_type = std::mbstate_t;

        static void assign(char_type &r, const char_type &a) { r = a; }
        static bool eq(char_type a, char_type b) { return a == b; }
        static bool lt(char_type a, char_type b) { return a < b; }
        static int compare(const char_type *s1, const char_type *s2, size_t n) {
            for (size_t i = 0; i < n; ++i)
                if (!eq(s1[i], s2[i])) return lt(s1[i], s2[i]) ? -1 : 1;
            return 0;
        }
        static size_t length(const char_type *s) {
            size_t len = 0;
            while (!eq(s[len], 0)) ++len;
            return len;
        }
        static const char_type *find(const char_type *s, size_t n, const char_type &a) {
            for (size_t i = 0; i < n; ++i)
                if (eq(s[i], a)) return s + i;
            return nullptr;
        }
        static char_type *move(char_type *dest, const char_type *src, size_t n) {
            return static_cast<char_type *>(memmove(dest, src, n * sizeof(char_type)));
        }
        static char_type *copy(char_type *dest, const char_type *src, size_t n) {
            return static_cast<char_type *>(memcpy(dest, src, n * sizeof(char_type)));
        }
        static char_type *assign(char_type *s, size_t n, char_type a) {
            for (size_t i = 0; i < n; ++i) s[i] = a;
            return s;
        }
        static int_type eof() { return static_cast<int_type>(-1); }
        static char_type to_char_type(int_type c) { return static_cast<char_type>(c); }
        static int_type to_int_type(char_type c) { return static_cast<int_type>(c); }
        static bool eq_int_type(int_type c1, int_type c2) { return c1 == c2; }
        static int_type not_eof(int_type c) { return c == eof() ? 0 : c; }
    };
};
