/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanBuilder
*/

#include "PacmanGame.hpp"
#include "Assets/ghosts/green_bottom.hpp"
#include "Assets/ghosts/orange_bottom.hpp"
#include "Assets/ghosts/pink_bottom.hpp"
#include "Assets/ghosts/red_bottom.hpp"
#include "Assets/ghosts/vulnerable_bottom.hpp"
#include "Assets/map/gum.hpp"
#include "Assets/map/pacgum.hpp"
#include "Assets/map/map.hpp"
#include "Assets/pac/pac_bottom_4.hpp"

extern "C" {
    arcade::game::IGame *create(void)
    {
        return new arcade::game::PacmanGame();
    }

    void destroy(arcade::game::IGame *game)
    {
        delete game;
    }

    arcade::types::LibType getType(void)
    {
        return arcade::types::GAME;
    }

    const char *getName()
    {
        return "PACMAN";
    }
}

arcade::game::PacmanGame::PacmanGame() : _direction(types::LEFT),
    _wantedDirection(types::LEFT), _extraLifes(2), _timer(0)
{
    initGameMap();
    initGameEntities();

    addEntity(types::EMPTY, types::TEXT, (types::Position){2, 2}, ' ',
        getRGBA(255, 255, 255, 255).color, "score : 0");
}

arcade::game::PacmanGame::~PacmanGame()
{
    clearEntities();
}

arcade::types::EntityType arcade::game::PacmanGame::getEntityType(char c)
{
    switch (c) {
        case WALL:
            return types::WALL;
        case GUM:
            return types::FOOD;
        case GUM2:
            return types::FOOD;
        case DOOR:
            return types::OBSTACLE;
        default:
            return types::EMPTY;
    }
}

arcade::types::EntityDraw arcade::game::PacmanGame::getEntityDraw(char c)
{
    switch (c) {
        case GUM:
            return types::SPRITE;
        case GUM2:
            return types::SPRITE;
        default:
            return types::NONE;
    }
}

arcade::types::Sprite arcade::game::PacmanGame::getEntitySprite(char c)
{
    switch (c) {
        case GUM:
            return {.key = "Gum", .assets = gum_png, .length = gum_png_len};
        case GUM2:
            return {.key = "Gum2", .assets = pacgum_png, .length = pacgum_png_len};
        default:
            return {};
    }
}

arcade::types::Position arcade::game::PacmanGame::getPosition(int y, int x)
{
    types::Position pos;

    pos.x = x;
    pos.y = y + MAP_MARGIN_TOP;
    return pos;
}

void arcade::game::PacmanGame::removeGameEntities()
{
    std::vector<types::Position> toDelete;

    for (auto &it : _entities[types::SPRITE])
        if (it.display_char == BLINKY || it.display_char == PINKY ||
        it.display_char == INKY || it.display_char == CLYDE ||
        it.display_char == PAC)
            toDelete.push_back(it.pos);
    for (auto &pos : toDelete)
        removeEntityAt(pos);
}

void arcade::game::PacmanGame::initGameEntities()
{
    addEntity(types::PLAYER, types::SPRITE, getPosition(16, 13), PAC, 0, "",
    {.key = "Pacman", .assets = pac_bottom_4_png, .length = pac_bottom_4_png_len});
    _pacPos = {13, 16};

    addEntity(types::ENEMY, types::SPRITE, getPosition(13, 13), BLINKY, 0, "",
    {.key = "Blinky", .assets = red_bottom_png, .length = red_bottom_png_len});

    addEntity(types::ENEMY, types::SPRITE, getPosition(14, 12), PINKY, 0, "",
    {.key = "Pinky", .assets = pink_bottom_png, .length = pink_bottom_png_len});

    addEntity(types::ENEMY, types::SPRITE, getPosition(14, 13), INKY, 0, "",
    {.key = "Inky", .assets = green_bottom_png, .length = green_bottom_png_len});

    addEntity(types::ENEMY, types::SPRITE, getPosition(14, 14), CLYDE, 0, "",
    {.key = "Clyde", .assets = orange_bottom_png, .length = orange_bottom_png_len});
}

void arcade::game::PacmanGame::initGameMap()
{
    addEntity(types::EMPTY, types::SPRITE, getPosition(0, 0), WALL, 0, "",
    {.key = "Background", .assets = map_png, .length = map_png_len});

    for (int y = 0; y < MAP_SIDE; ++y)
        for (int x = 0; x < MAP_SIDE; ++x) {
            types::EntityDraw entityDraw = getEntityDraw(_pacMap[y][x]);

            if (entityDraw != types::NONE)
                addEntity(getEntityType(_pacMap[y][x]), entityDraw,
                getPosition(y, x), _pacMap[y][x],
                0, "", getEntitySprite(_pacMap[y][x]));
        }
}
