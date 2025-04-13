/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Config
*/

/**
 * @file includes.hpp
 * @brief Defines the specials structures and types used by the Pacman game.
 * @author Jason KOENIG
 * @version 1.0
 * @date 2025-04-13
 *
 * @details
 * Contains all the structures used in the Pacman game. In particular,
 * it contains the entity id, the ghost mode and the map defined in static constexpr.
 *
 * @see arcade::game::pacman
 */
#ifndef CONFIG_HPP_
    #define CONFIG_HPP_
    #define MAP_SIDE 30
    #define MAP_MARGIN_TOP 6
    #define TIME_1_SEC 12
    #include "../../../include/Types.hpp"

namespace arcade::game::pacman {
    /**
     * @enum GameEntity
     * @brief Contains entity id.
     * @details Contains the id of the entities, which is used to differentiate
     * their actions and enable the builder to function. It it also used as
     * representation in non-graphical libraries such as the Ncurses.
     * Pac is a character played by the player. Blinky, Pinky, Inky and Clyde
     * are the ghosts who seek to kill the player.
     * @see PacmanFactory.cpp
     */
    enum GameEntity {
        PAC = 'O',          ///< Pac 
        BLINKY = 'B',       ///< Blinky
        INKY = 'I',         ///< Inky
        PINKY = 'P',        ///< Pinky
        CLYDE = 'C',        ///< Clyde
        GUM = '.',          ///< Pac's basic food. Releases more ghosts the more he eats (max 4).
        GUM2 = 'G',         ///< Pac food that allows him to eat ghosts instead of being eaten
        WALL = '#',         ///< Maze's wall
        DOOR = '_',         ///< Door that locks ghosts in the center of the maze.
        APPLE = 'a',        ///< An apple that gives 200 pts to the player.
        BANANA = 'b',       ///< A banana that gives 500 pts to the player.
        CHERRIES = 'c',     ///< Cherries that gives 800 pts to the player.
        PINEAPPLE = 'p',    ///< A pineapple that gives 1500 pts to the player.
        POTION = 'u',       ///< A potion that gives 3000 pts to the player.
        KEY = 'k',          ///< A key that gives 5000 pts to the player.
        LIFE = 'L',         ///< Representation of an extra life for the player, preventing him from dying if killed by a ghost.
        VULNERABLE = 'V',   ///< Ghost appearance when in frightened mode.
        DEAD = 'D'          ///< Ghost appearance when in eaten mode.
    };

    /**
     * @enum GhostMode
     * @brief Contains ghosts mode.
     * @details Contains displacement states / possible ghost behaviors.
     */
    enum GhostMode {
        SCATTER,    ///< Ghosts move to their corner of the maze and then circle around.
        CHASE,      ///< Ghosts try to kill the player using their unique attack patterns.
        FRIGHTENED, ///< Ghosts reverse their direction and then move at random.
        EATEN       ///< Ghosts move to the center of the maze to be resurrected.
    };

    static constexpr const char *pacMap[] = {
        "############## ###############",
        "#............# #.............#",
        "#.####.#####.# #.######.####.#",
        "#G#  #.#   #.# #.#    #.#  #G#",
        "#.####.#####.###.######.####.#",
        "#............................#",
        "#.####.##.##########.##.####.#",
        "#.####.##.#### #####.##.####.#",
        "#......##....# #.....##......#",
        "######.#####.# #.######.######",
        "     #.##### ### ######.#     ",
        "     #.##         ...##.#     ",
        "     #.##  ##_## ##..##.#     ",
        "######.##  #   # ##..##.######",
        " .......   #   # ##.......... ",
        "######.##  ##### ##..##.######",
        "     #.##        ##..##.#     ",
        "     #.##   ###  ##..##.#     ",
        "     #.## #########..##.#     ",
        "######.##.#### ####..##.######",
        "#............# #.............#",
        "#.####.#####.# #.#####..####.#",
        "#.####.#####.###.#####..####.#",
        "#G..##..................##..G#",
        "###.##.##.#########.##..##.###",
        "###.##.##.#### ####.##..##.###",
        "#......##....# #....##.......#",
        "#.##########.###.###########.#",
        "#............................#",
        "##############################"
    };
};

#endif
