/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Player
*/

/**
* @file Player.cpp
* @brief Implements Pacman player logic (movement, direction, lives).
* @author Jason Koenig
* @version 1.0
* @date 2025-04-14
* @details
* This file defines the behavior of the Pacman player entity, including
* input handling, movement constraints (walls, doors), position updates,
* and life/kill state.

* @see arcade::game::pacman::Player
*/
#include "Player.hpp"

/**
* @brief Default constructor for Player.
* Initializes the player with default direction, position (0, 0),
* 2 extra lives and no kills.
*/
arcade::game::pacman::Player::Player() : _direction(types::LEFT),
    _wantedDirection(types::LEFT), _position({0, 0}),
    _extraLifes(2), _killRow(0)
{
}

/**
* @brief Destructor for Player.
*/
arcade::game::pacman::Player::~Player()
{
}

/**
* @brief Computes the next position based on current direction.
* @return The expected position if movement occurs.
*/ 
arcade::types::Position arcade::game::pacman::Player::getNextPos()
{
    types::Position pos = {_position.x, _position.y};

    switch (_direction) {
        case types::UP:
            --pos.y;
            break;
        case types::LEFT:
            --pos.x;
            break;
        case types::RIGHT:
            ++pos.x;
            break;
        default:
            ++pos.y;
            break;
    }
    return pos;
}

/**
* @brief Accessor for the current player position.
* @return A reference to the current in-map coordinates.
*/
arcade::types::Position &arcade::game::pacman::Player::getPos()
{
    return _position;
}

/**
* @brief Returns the visual/real position of the player.
* @details Accounts for the vertical margin used in rendering (MAP_MARGIN_TOP).
* @return The adjusted position.
*/
arcade::types::Position arcade::game::pacman::Player::getRealPos()
{
    return {_position.x, _position.y + MAP_MARGIN_TOP};
}

/**
* @brief Returns the current movement direction.
* @return The current direction (UP, DOWN, LEFT, RIGHT).
*/
arcade::types::Direction arcade::game::pacman::Player::getDirection() const
{
    return _direction;
}

/**
* @brief Returns the number of extra lives remaining.
* @return Number of lives left after the initial one.
*/
int arcade::game::pacman::Player::getExtraLifes() const
{
    return _extraLifes;
}

/**
* @brief Returns the number of ghosts eaten in the current power-up streak.
* @return Kill streak counter.
*/
int arcade::game::pacman::Player::getKillRow() const
{
    return _killRow;
}

/**
* @brief Sets both the current and target direction of the player.
* @param direction The new direction.
*/
void arcade::game::pacman::Player::setDirection(types::Direction direction)
{
    _direction = direction;
    _wantedDirection = direction;
}

/**
* @brief Forces the player's position.
* @param y Vertical coordinate (map units).
* @param x Horizontal coordinate (map units).
*/
void arcade::game::pacman::Player::setPosition(int y, int x)
{
    _position.x = x;
    _position.y = y;
}

/**
* @brief Sets the number of extra lives.
* @param extraLifes New value.
*/
void arcade::game::pacman::Player::setExtraLifes(int extraLifes)
{
    _extraLifes = extraLifes;
}

/**
* @brief Sets the ghost kill streak counter.
* @param killRow New value.
*/
void arcade::game::pacman::Player::setKillRow(int killRow)
{
    _killRow = killRow;
}

/**
* @brief Updates current direction based on wanted direction and map constraints.
* @details
* If the direction change requested by the player is valid (i.e. the tile in
* that direction is not a WALL or DOOR), the current direction is updated.
*/
void arcade::game::pacman::Player::updateWantedDirection()
{
    switch (_wantedDirection) {
        case types::UP:
            if (pacMap[_position.y - 1][_position.x] != WALL &&
            pacMap[_position.y - 1][_position.x] != DOOR)
                _direction = _wantedDirection;
            return;
        case types::LEFT:
            if (pacMap[_position.y][_position.x - 1] != WALL &&
            pacMap[_position.y][_position.x - 1] != DOOR)
                _direction = _wantedDirection;
            return;
        case types::RIGHT:
            if (pacMap[_position.y][_position.x + 1] != WALL &&
            pacMap[_position.y][_position.x + 1] != DOOR)
                _direction = _wantedDirection;
            return;
        default:
            if (pacMap[_position.y + 1][_position.x] != WALL &&
            pacMap[_position.y + 1][_position.x] != DOOR)
                _direction = _wantedDirection;
            return;
    }
}

/**
* @brief Processes input and updates movement direction accordingly.
* @param event The player input (directional).
* @details
* The method checks if the requested direction is valid and updates either
* the direction immediately or sets it as the wanted direction to try later.
* @see updateWantedDirection()
*/
void arcade::game::pacman::Player::updateDirection(types::InputEvent event)
{
    switch (event) {
        case types::AKEY_UP:
            if (pacMap[_position.y - 1][_position.x] != WALL &&
            pacMap[_position.y - 1][_position.x] != DOOR) {
                _direction = types::UP;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::UP;
            return;
        case types::AKEY_LEFT:
            if (pacMap[_position.y][_position.x - 1] != WALL &&
            pacMap[_position.y][_position.x - 1] != DOOR) {
                _direction = types::LEFT;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::LEFT;
            return;
        case types::AKEY_RIGHT:
            if (pacMap[_position.y][_position.x + 1] != WALL &&
            pacMap[_position.y][_position.x + 1] != DOOR) {
                _direction = types::RIGHT;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::RIGHT;
            return;
        case types::AKEY_DOWN:
            if (pacMap[_position.y + 1][_position.x] != WALL &&
            pacMap[_position.y + 1][_position.x] != DOOR) {
                _direction = types::DOWN;
                _wantedDirection = _direction;
            } else
                _wantedDirection = types::DOWN;
            return;
        default:
            return updateWantedDirection();
    }
}

/**
* @brief Moves the player entity to the new coordinates and updates its internal position.
* @param y Target vertical coordinate (map).
* @param x Target horizontal coordinate (map).
* @param player Pointer to the player entity object (used for rendering or collisions).
* @details
* Handles teleportation if the player exits the map bounds (left/right side).
*/
void arcade::game::pacman::Player::move(int y, int x, types::Entity *player)
{
    if (x == -1)
        x = 29;
    else if (x == 30)
        x = 0;
    player->pos.x = x;
    player->pos.y = y + MAP_MARGIN_TOP;
    _position = {x, y};   
}
