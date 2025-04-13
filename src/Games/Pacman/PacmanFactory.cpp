/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanFactory
*/

#include "PacmanGame.hpp"

#include "Assets/ghosts/green_bottom.hpp"
#include "Assets/ghosts/orange_bottom.hpp"
#include "Assets/ghosts/pink_bottom.hpp"
#include "Assets/ghosts/red_bottom.hpp"
#include "Assets/ghosts/vulnerable_bottom.hpp"
#include "Assets/map/pacgum.hpp"
#include "Assets/map/gum.hpp"
#include "Assets/map/map.hpp"
#include "Assets/pac/pac_bottom_1.hpp"
#include "Assets/life.hpp"
#include "Assets/fruits/apple.hpp"
#include "Assets/fruits/banana.hpp"
#include "Assets/fruits/cherries.hpp"
#include "Assets/fruits/key.hpp"
#include "Assets/fruits/pineapple.hpp"
#include "Assets/fruits/potion.hpp"

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

arcade::game::PacmanGame::PacmanGame() : _dotCpt(0), _level(1), _timer(0), _fruitTimer(0)
{
    addEntity(types::EMPTY, types::SPRITE, getPosition(0, 0),
    pacman::WALL, getEntityColor(pacman::WALL).color, "",
    {.key = "Background", .assets = map_png, .length = map_png_len});

    initGameMap();
    initGameEntities();
    loadHighScore();

    addEntity(types::EMPTY, types::TEXT, (types::Position){2, 2}, ' ',
    getRGBA(255, 255, 255, 255).color,
    "level 1   score 0   high score " + std::to_string(_highScore));

    addEntity(types::EMPTY, types::SPRITE, (types::Position){3, 37}, pacman::LIFE,
    getRGBA(255, 255, 255, 255).color, "", getEntitySprite(pacman::LIFE));

    addEntity(types::EMPTY, types::SPRITE, (types::Position){1, 37}, pacman::LIFE,
    getRGBA(255, 255, 255, 255).color, "", getEntitySprite(pacman::LIFE));

    _playerStartPos = getPosition(16, 13);
}

arcade::game::PacmanGame::~PacmanGame()
{
    saveHighScore();
    clearEntities();
}

int arcade::game::PacmanGame::getFoodValue(char food)
{
    switch (food) {
        case pacman::GUM:
            ++_dotCpt;
            --_remainingDots;
            return 10;
        case pacman::GUM2:
            ++_dotCpt;
            --_remainingDots;
            _player.setKillRow(0);
            setGhostsFrightened();
            return 50;
        case pacman::APPLE:
            return 200;
        case pacman::BANANA:
            return 500;
        case pacman::CHERRIES:
            return 800;
        case pacman::PINEAPPLE:
            return 1500;
        case pacman::POTION:
            return 3000;
        case pacman::KEY:
            return 5000;
        default:
            break;
    }
    if (food != pacman::PINKY && food != pacman::CLYDE &&
    food != pacman::BLINKY && food != pacman::INKY)
        return 0;
    switch (_player.getKillRow()) {
        case 0:
            return 200;
        case 1:
            return 400;
        case 2:
            return 800;
        default:
            return 1600;
    }
    refreshScore();
}

arcade::types::EntityType arcade::game::PacmanGame::getEntityType(char c)
{
    switch (c) {
        case pacman::WALL:
            return types::WALL;
        case pacman::GUM:
            return types::FOOD;
        case pacman::GUM2:
            return types::FOOD;
        case pacman::DOOR:
            return types::OBSTACLE;
        default:
            return types::EMPTY;
    }
}

arcade::types::EntityDraw arcade::game::PacmanGame::getEntityDraw(char c)
{
    switch (c) {
        case pacman::GUM:
            return types::SPRITE;
        case pacman::GUM2:
            return types::SPRITE;
        default:
            return types::NONE;
    }
}

arcade::types::color_t arcade::game::PacmanGame::getEntityColor(char c)
{
    switch (c) {
        case pacman::PAC:
            return getRGBA(255, 255, 0, 255);
        case pacman::BLINKY:
            return getRGBA(255, 0, 0, 255);
        case pacman::INKY:
            return getRGBA(0, 255, 0, 255);
        case pacman::PINKY:
            return getRGBA(255, 192, 203, 255);
        case pacman::CLYDE:
            return getRGBA(255, 165, 0, 255);
        case pacman::VULNERABLE:
            return getRGBA(0, 0, 255, 255);
        default:
            return getRGBA(255, 255, 255, 255);
    }
}

arcade::types::Sprite arcade::game::PacmanGame::getEntitySprite(char c)
{
    switch (c) {
        case pacman::GUM:
            return {.key = "Gum", .assets = gum_png, .length = gum_png_len};
        case pacman::GUM2:
            return {.key = "Gum2", .assets = pacgum_png, .length = pacgum_png_len};
        case pacman::LIFE:
            return {.key = "Life", .assets = life_png, .length = life_png_len};
        case pacman::PAC:
            return {.key = "Pacman", .assets = pac_bottom_1_png, .length = pac_bottom_1_png_len};
        case pacman::BLINKY:
            return {.key = "Blinky", .assets = red_bottom_png, .length = red_bottom_png_len};
        case pacman::PINKY:
            return {.key = "Pinky", .assets = pink_bottom_png, .length = pink_bottom_png_len};
        case pacman::INKY:
            return {.key = "Inky", .assets = green_bottom_png, .length = green_bottom_png_len};
        case pacman::CLYDE:
            return {.key = "Clyde", .assets = orange_bottom_png, .length = orange_bottom_png_len};
        case pacman::VULNERABLE:
            return {.key = "Vulnerable", .assets = vulnerable_bottom_png,
                .length = vulnerable_bottom_png_len};
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

arcade::types::Entity *arcade::game::PacmanGame::getEntityAtByChar(char c)
{
    for (auto &pair : _entities) {
        auto &entitiesVec = pair.second;

        for (auto it = entitiesVec.begin(); it != entitiesVec.end(); it++)
            if ((*it).display_char == c)
                return &(*it);
    }
    return nullptr;
}

int arcade::game::PacmanGame::getCycleTime()
{
    if (_level > 8)
        return 2;
    if (_level > 6)
        return 3;
    if (_level > 4)
        return 4;
    if (_level > 2)
        return 5;
    return 6;
}

void arcade::game::PacmanGame::removeEntityAtByChar(char c)
{
    for (auto &pair : _entities) {
        auto &entitiesVec = pair.second;
        for (auto it = entitiesVec.begin(); it != entitiesVec.end(); ++it)
            if ((*it).display_char == c) {
                entitiesVec.erase(it);
                return;
            }
    }
}

void arcade::game::PacmanGame::resetGameEntities()
{
    _player.setPosition(16, 13);
    getEntityAtByChar(pacman::PAC)->pos = getPosition(16, 13);
    _blinky.setPosition(11, 13);
    getEntityAtByChar(pacman::BLINKY)->pos = getPosition(11, 13);
    _pinky.setPosition(14, 12);
    getEntityAtByChar(pacman::PINKY)->pos = getPosition(14, 12);
    _inky.setPosition(14, 13);
    getEntityAtByChar(pacman::INKY)->pos = getPosition(14, 13);
    _clyde.setPosition(14, 14);
    getEntityAtByChar(pacman::CLYDE)->pos = getPosition(14, 14);

    _player.setDirection(types::LEFT);
    _blinky.setDirection(types::UP);
    _pinky.setDirection(types::UP);
    _inky.setDirection(types::UP);
    _clyde.setDirection(types::UP);

    _blinky.setMode(pacman::SCATTER);
    _pinky.setMode(pacman::SCATTER);
    _inky.setMode(pacman::SCATTER);
    _clyde.setMode(pacman::SCATTER);
}

void arcade::game::PacmanGame::initGameEntities()
{
    addEntity(types::PLAYER, types::SPRITE, getPosition(16, 13), pacman::PAC,
    getEntityColor(pacman::PAC).color, "", getEntitySprite(pacman::PAC));

    addEntity(types::ENEMY, types::SPRITE, getPosition(12, 13), pacman::BLINKY,
    getEntityColor(pacman::BLINKY).color, "", getEntitySprite(pacman::BLINKY));

    addEntity(types::ENEMY, types::SPRITE, getPosition(14, 12), pacman::PINKY,
    getEntityColor(pacman::PINKY).color, "", getEntitySprite(pacman::PINKY));

    addEntity(types::ENEMY, types::SPRITE, getPosition(14, 13), pacman::INKY,
    getEntityColor(pacman::INKY).color, "", getEntitySprite(pacman::INKY));

    addEntity(types::ENEMY, types::SPRITE, getPosition(14, 14), pacman::CLYDE,
    getEntityColor(pacman::CLYDE).color, "", getEntitySprite(pacman::CLYDE));

    resetGameEntities();
}

void arcade::game::PacmanGame::initGameMap()
{
    _remainingDots = 0;

    for (int y = 0; y < MAP_SIDE; ++y)
        for (int x = 0; x < MAP_SIDE; ++x) {
            types::EntityDraw entityDraw = getEntityDraw(pacman::pacMap[y][x]);
            types::EntityType entityType = getEntityType(pacman::pacMap[y][x]);

            if (entityType == types::FOOD)
                ++_remainingDots;
            if (!(entityDraw == types::NONE && entityType == types::EMPTY))
                addEntity(entityType, entityDraw, getPosition(y, x),
                pacman::pacMap[y][x], getEntityColor(pacman::pacMap[y][x]).color, "",
                getEntitySprite(pacman::pacMap[y][x]));
        }
}

void arcade::game::PacmanGame::generateFood()
{
    if (getEntityAt(_playerStartPos))
        return;
    _fruitTimer = 0;
    switch (_level) {
        case 1:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::APPLE,
            getEntityColor(pacman::APPLE).color, "",
            {.key = "Apple", .assets = apple_png, .length = apple_png_len});
            return;
        case 2:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::BANANA,
            getEntityColor(pacman::BANANA).color, "",
            {.key = "Banana", .assets = banana_png, .length = banana_png_len});
            return;
        case 3:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::CHERRIES,
            getEntityColor(pacman::CHERRIES).color, "",
            {.key = "Cherries", .assets = cherries_png, .length = cherries_png_len});
            return;
        case 4:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::PINEAPPLE,
            getEntityColor(pacman::PINEAPPLE).color, "",
            {.key = "Pineapple", .assets = pineapple_png, .length = pineapple_png_len});
            return;
        case 5:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::POTION,
            getEntityColor(pacman::POTION).color, "",
            {.key = "Potion", .assets = potion_png, .length = potion_png_len});
            return;
        default:
            addEntity(types::FOOD, types::SPRITE, _playerStartPos, pacman::KEY,
            getEntityColor(pacman::KEY).color, "",
            {.key = "Key", .assets = key_png, .length = key_png_len});
            return;
    }
}

void arcade::game::PacmanGame::exitGhostSpecialModes(pacman::Ghost &ghost)
{
    pacman::GhostMode mode = ghost.getMode();
    size_t timer = ghost.getTimer();
    types::Position &pos = ghost.getPosition();

    switch (mode) {
        case pacman::FRIGHTENED:
            ++timer;
            if (timer % (TIME_1_SEC * 10) == 0) {
                ghost.setTimer(0);
                unsetFrightenedSkin(ghost.getId());
                ghost.loadLastMode();
                return;
            }
            ghost.setTimer(timer);
            return;
        case pacman::EATEN:
            if (pos.x == 13 && pos.y == 14) {
                ghost.loadLastMode();
                unsetFrightenedSkin(ghost.getId());
            }
            return;
        default:
            return;
    }
}

void arcade::game::PacmanGame::setGhostsFrightened()
{
    if (_blinky.getMode() != pacman::EATEN &&
    _blinky.getMode() != pacman::FRIGHTENED) {
        setFrightenedSkin(pacman::BLINKY);
        _blinky.setMode(pacman::FRIGHTENED);
    }
    if (_pinky.getMode() != pacman::EATEN &&
    _pinky.getMode() != pacman::FRIGHTENED) {
        setFrightenedSkin(pacman::PINKY);
        _pinky.setMode(pacman::FRIGHTENED);
    }
    if (_inky.getMode() != pacman::EATEN &&
    _inky.getMode() != pacman::FRIGHTENED) {
        setFrightenedSkin(pacman::INKY);
        _inky.setMode(pacman::FRIGHTENED);
    }
    if (_clyde.getMode() != pacman::EATEN &&
    _clyde.getMode() != pacman::FRIGHTENED) {
        setFrightenedSkin(pacman::CLYDE);
        _clyde.setMode(pacman::FRIGHTENED);
    }
}

void arcade::game::PacmanGame::setFrightenedSkin(char c)
{
    types::Entity *ghost = getEntityAtByChar(c);

    if (ghost) {
        ghost->color = getEntityColor(pacman::VULNERABLE).color;
        ghost->sprite = getEntitySprite(pacman::VULNERABLE);
    }
}

void arcade::game::PacmanGame::unsetFrightenedSkin(char c)
{
    types::Entity *ghost = getEntityAtByChar(c);

    if (ghost) {
        ghost->color = getEntityColor(c).color;
        ghost->sprite = getEntitySprite(c);
    }
}
