/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanGame
*/

#include "PacmanGame.hpp"
#include "Assets/pac/pac.hpp"

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

arcade::game::PacmanGame::PacmanGame()
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
        memset(_entities[y], 0, MAP_WIDTH);

    _entities[17][14] = 'P';
    _entities[14][11] = 'A';
    _entities[14][13] = 'B';
    _entities[14][15] = 'C';
    _entities[13][13] = 'D';
    // addEntity(getEntityType('P'), getEntityDraw('P'),
    // (arcade::types::Position){17, 14}, 'P', getEntityColor('P').color, "",
    // {.key = "Pacman", .assets = pac_png, .length = pac_png_len});

    for (int y = 0; y < MAP_HEIGHT; ++y)
        for (int x = 0; x < MAP_WIDTH; ++x) {
            types::EntityDraw entityDraw = getEntityDraw(_pacmap[y][x]);

            if (entityDraw != types::NONE)
                addEntity(getEntityType(_pacmap[y][x]), entityDraw,
                (arcade::types::Position){x, y}, _pacmap[y][x],
                getEntityColor(_pacmap[y][x]).color, "");
        }
}

arcade::game::PacmanGame::~PacmanGame()
{
    clearEntities();
}

void arcade::game::PacmanGame::update(const std::pair<types::Position, types::InputEvent> event)
{
    (void)event;
}

arcade::types::EntityType arcade::game::PacmanGame::getEntityType(char c)
{
    switch (c) {
        case '0':
            return types::WALL;
        case '.':
            return types::COLLECTIBLE;
        case 'G':
            return types::FOOD;
        case '_':
            return types::OBSTACLE;
        case 'P':
            return types::PLAYER;
        default:
            return types::EMPTY;
    }
}

arcade::types::EntityDraw arcade::game::PacmanGame::getEntityDraw(char c)
{
    switch (c) {
        case '0':
            return types::RECTANGLE;
        case '.':
            return types::CIRCLE;
        case 'G':
            return types::CIRCLE;
        case '_':
            return types::RECTANGLE;
        case 'P':
            return types::SPRITE;
        default:
            return types::NONE;
    }
}

arcade::types::color_t arcade::game::PacmanGame::getEntityColor(char c)
{
    switch (c) {
        case '0':
            return getRGBA(62, 78, 249, 255);
        case '.':
            return getRGBA(255, 255, 0, 255);
        case 'G':
            return getRGBA(255, 255, 0, 255);
        case '_':
            return getRGBA(62, 249, 233, 255);
        case 'P':
            return getRGBA(255, 255, 0, 255);
        default:
            return getRGBA(0, 0, 0, 255);
    }
}
