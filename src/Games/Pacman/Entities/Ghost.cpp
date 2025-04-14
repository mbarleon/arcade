/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Ghost
*/

#include "Ghost.hpp"

/**
 * @brief Constructor of the Ghost class.
 * @details Initializes a ghost instance with default values:
 * starting position, direction, mode, and timer.
 */
arcade::game::pacman::Ghost::Ghost() : _direction(types::UP),
    _position({0, 0}), _mode(EATEN), _timer(0)
{
}

/**
 * @brief Default destructor.
 * @details Destroys the Ghost instance. No special cleanup is required.
 */
arcade::game::pacman::Ghost::~Ghost()
{
}

/**
 * @brief Teleports the ghost.
 * @details Sets the ghost's position to the specified coordinates.
 *
 * @param y The Y-coordinate after teleportation.
 * @param x The X-coordinate after teleportation.
 */
void arcade::game::pacman::Ghost::setPosition(int y, int x)
{
    _position.x = x;
    _position.y = y;
}

/**
 * @brief Changes the direction of the ghost.
 * @details Updates the internal direction variable of the Ghost instance
 * to alter its movement direction.
 *
 * @param direction The new direction to assign to the ghost.
 */
void arcade::game::pacman::Ghost::setDirection(types::Direction direction)
{
    _direction = direction;
}

/**
 * @brief Reverses the ghost's direction.
 * @details This function updates the ghost's current direction to its opposite,
 * based on its current movement.
 */
void arcade::game::pacman::Ghost::reverseDirection()
{
    switch (_direction) {
        case types::UP:
            _direction = types::DOWN;
            break;
        case types::LEFT:
            _direction = types::RIGHT;
            break;
        case types::RIGHT:
            _direction = types::LEFT;
            break;
        default:
            _direction = types::UP;
            break;
    }
}

/**
 * @brief Sets the ghost's timer.
 * @details Updates the internal timer value of the ghost with the given value.
 *
 * @param timer The new timer value to set.
 */
void arcade::game::pacman::Ghost::setTimer(size_t timer)
{
    _timer = timer;
}

/**
 * @brief Changes the ghost's behavior mode.
 * @details Sets the ghost's current mode (e.g., CHASE, SCATTER, FRIGHTENED, EATEN).
 * In certain cases (e.g., switching to FRIGHTENED or SCATTER from CHASE),
 * the ghost will reverse its direction. Also manages internal transitions between
 * modes and stores the previous mode when necessary.
 *
 * @param mode The new behavior mode to assign to the ghost.
 */
void arcade::game::pacman::Ghost::setMode(GhostMode mode)
{
    if (mode == FRIGHTENED || mode == CHASE ||
    (mode == SCATTER && _mode == CHASE))
        reverseDirection();
    if (mode == FRIGHTENED) {
        _timer = 0;
        _lastMode = _mode;
    } else if (mode == EATEN) {
        _mode = mode;
        return;
    }
    if (_mode == FRIGHTENED)
        _lastMode = mode;
    else
        _mode = mode;
}

/**
 * @brief Restores the previous behavior mode.
 * @details Loads the last saved mode into the current one, typically used to
 * return to the normal state after a temporary mode like FRIGHTENED has ended.
 */
void arcade::game::pacman::Ghost::loadLastMode()
{
    _mode = _lastMode;
}

/**
 * @brief Resets the internal map state.
 * @details This function is used to prepare the map before computing the
 * distance between the ghost and the player, typically for pathfinding purposes.
 */
void arcade::game::pacman::Ghost::resetTargetMap()
{
    for (int y = 0; y < MAP_SIDE; ++y)
        for (int x = 0; x < MAP_SIDE; ++x)
            _targetMap[y][x] = -1;
}

/**
 * @brief Computes a random valid movement direction for the ghost.
 * @details This function selects one of the possible directions (up, down, left, or right),
 * ensuring the ghost cannot move through walls or doors, and avoiding direct reversal
 * of its current direction unless necessary. It also includes special conditions when
 * the ghost is within certain coordinates (e.g., tunnel areas or the ghost house).
 *
 * @return A valid direction chosen at random, or UP by default if no other is found.
 */
arcade::types::Direction arcade::game::pacman::Ghost::getRandomDirection()
{
    bool directions[4] = {true, true, true, true};
    int possibleDirections = 0;
    int nextDirection;

    if ((_position.x >= 12 && _position.x <= 14) &&
    (_position.y >= 12 && _position.y <= 14))
        return getTargetDirection(11, 13);
    if (_position.y == 14 && ((_position.x >= 0 && _position.x <= 4) ||
    (_position.x >= 25 && _position.x <= 29)))
        return _direction;
    if ((_position.y == 11 || _position.y == 23) &&
    (_position.x >= 12 && _position.x <= 17)) {
        if (_direction == types::LEFT)
            return types::LEFT;
        if (_direction == types::RIGHT)
            return types::RIGHT;
    }
    switch (_direction) {
        case types::DOWN:
            directions[types::UP] = false;
            break;
        case types::LEFT:
            directions[types::RIGHT] = false;
            break;
        case types::RIGHT:
            directions[types::LEFT] = false;
            break;
        default:
            directions[types::DOWN] = false;
            break;
    }
    if (pacMap[_position.y - 1][_position.x] == WALL ||
    pacMap[_position.y - 1][_position.x] == DOOR)
        directions[types::UP] = false;
    if ((pacMap[_position.y][_position.x - 1] == WALL ||
    pacMap[_position.y][_position.x - 1] == DOOR))
        directions[types::LEFT] = false;
    if ((pacMap[_position.y][_position.x + 1] == WALL ||
    pacMap[_position.y][_position.x + 1] == DOOR))
        directions[types::RIGHT] = false;
    if (pacMap[_position.y + 1][_position.x] == WALL ||
    pacMap[_position.y + 1][_position.x] == DOOR)
        directions[types::DOWN] = false;
    for (int i = 0; i < 4; ++i)
        if (directions[i])
            ++possibleDirections;
    for (nextDirection = rand() % possibleDirections; nextDirection < 4; ++nextDirection)
        if (directions[nextDirection])
            return static_cast<types::Direction>(nextDirection);
    return types::UP;
}

/**
 * @brief Populates the target map recursively from a given slot.
 * @details This function sets the distance cost in the `_targetMap` at (y, x)
 * to `sum`, then recursively updates neighboring slots (up, down, left, right),
 * increasing `sum` by 1 at each step.
 *
 * It also handles wrapping around horizontally if `y == 14`, ensuring the ghost can
 * move through the tunnel on row 14, and stops recursion if it encounters walls or
 * boundaries.
 *
 * @param y The Y-coordinate of the current slot in the grid.
 * @param x The X-coordinate of the current slot in the grid.
 * @param sum The distance value to assign to this slot before recursing.
 */
void arcade::game::pacman::Ghost::populateTargetMapSlot(int y, int x, int sum)
{
    if (y == 14) {
        if (x == -1)
            x = 29;
        if (x == 30)
            x = 0;
    }
    if (y < 0 || x < 0 || y > 29 || x > 29 ||
    pacMap[y][x] == WALL)
        return;
    if (_targetMap[y][x] == -1 || sum < _targetMap[y][x]) {
        _targetMap[y][x] = sum;
        populateTargetMapSlot(y - 1, x, sum + 1);
        populateTargetMapSlot(y + 1, x, sum + 1);
        populateTargetMapSlot(y, x + 1, sum + 1);
        populateTargetMapSlot(y, x - 1, sum + 1);
    }
}

/**
 * @brief Calculates the best direction to reach a specific target position.
 * @details Uses a flood-fill style approach to compute distances in the `_targetMap`.
 * The function resets the map, sets the target cell (y, x) to distance 0, then propagates
 * outward via populateTargetMapSlot(). Finally, it checks the distances in each
 * neighboring cell of the ghost's current position to pick the minimal distance,
 * ensuring the ghost does not reverse its direction directly unless necessary.
 *
 * Special tunnel logic is applied for row 14, wrapping around horizontally.
 *
 * @param y The Y-coordinate of the target position.
 * @param x The X-coordinate of the target position.
 * @return The direction that yields the smallest distance towards the target.
 */
arcade::types::Direction arcade::game::pacman::Ghost::getTargetDirectionCorrected(int y, int x)
{
    int directions[4];

    resetTargetMap();
    _targetMap[_position.y][_position.x] = -2;
    _targetMap[y][x] = 0;

    populateTargetMapSlot(y - 1, x, 1);
    populateTargetMapSlot(y + 1, x, 1);
    populateTargetMapSlot(y, x + 1, 1);
    populateTargetMapSlot(y, x - 1, 1);

    if (_position.y == 14 && _position.x == 0) {
        directions[types::LEFT] = _targetMap[_position.y][29];
        directions[types::RIGHT] = _targetMap[_position.y][_position.x + 1];
    } else if (_position.y == 14 && _position.x == 29) {
        directions[types::LEFT] = _targetMap[_position.y][_position.x - 1];
        directions[types::RIGHT] = _targetMap[_position.y][0];
    } else {
        directions[types::LEFT] = _targetMap[_position.y][_position.x - 1];
        directions[types::RIGHT] = _targetMap[_position.y][_position.x + 1];
    }
    directions[types::UP] = (_position.y <= 1) ? -1 : _targetMap[_position.y - 1][_position.x];
    directions[types::DOWN] = (_position.y >= 28) ? -1 : _targetMap[_position.y + 1][_position.x];

    switch (_direction) {
        case types::UP:
            directions[types::DOWN] = -1;
            break;
        case types::LEFT:
            directions[types::RIGHT] = -1;
            break;
        case types::RIGHT:
            directions[types::LEFT] = -1;
            break;
        default:
            directions[types::UP] = -1;
            break;
    }
    if (directions[types::UP] != -1 && _direction != types::DOWN &&
    (directions[types::UP] <= directions[types::DOWN] || directions[types::DOWN] == -1) &&
    (directions[types::UP] <= directions[types::LEFT] || directions[types::LEFT] == -1) &&
    (directions[types::UP] <= directions[types::RIGHT] || directions[types::RIGHT] == -1))
        return types::UP;
    if (directions[types::LEFT] != -1 && _direction != types::RIGHT &&
    (directions[types::LEFT] <= directions[types::DOWN] || directions[types::DOWN] == -1) &&
    (directions[types::LEFT] <= directions[types::UP] || directions[types::UP] == -1) &&
    (directions[types::LEFT] <= directions[types::RIGHT] || directions[types::RIGHT] == -1))
        return types::LEFT;
    if (directions[types::DOWN] != -1 && _direction != types::UP &&
    (directions[types::DOWN] <= directions[types::RIGHT] || directions[types::RIGHT] == -1) &&
    (directions[types::DOWN] <= directions[types::LEFT] || directions[types::LEFT] == -1) &&
    (directions[types::DOWN] <= directions[types::UP] || directions[types::UP] == -1))
        return types::DOWN;
    return types::RIGHT;
}

/**
 * @brief Determines the best direction to reach a given target tile.
 * @details This function adjusts the target coordinates based on bounds,
 * wall collisions, and special tile behavior (e.g., corners, ghost house logic).
 * It applies corrections to handle tunnels, edge wrapping, or unreachable tiles,
 * and delegates to `getTargetDirectionCorrected()` for final distance-based evaluation.
 *
 * Specific behaviors:
 * - Ensures target is not outside the map or on a wall.
 * - Modifies movement in corners to ensure valid ghost turning.
 * - Redirects ghosts toward the ghost house center when not in EATEN mode.
 * - Maintains horizontal direction in specific SCATTER or CHASE situations.
 *
 * @param y The target Y-coordinate on the map.
 * @param x The target X-coordinate on the map.
 * @return The direction the ghost should take to get closer to the target.
 *
 * @see getTargetDirectionCorrected()
 */
arcade::types::Direction arcade::game::pacman::Ghost::getTargetDirection(int y, int x)
{
    if (x <= 0)
        x = (y == 14) ? 0 : 1;
    if (x >= 29)
        x = (y == 14) ? 29 : 28;
    if (y < 1)
        y = 1;
    if (y > 28)
        y = 28;
    if (pacMap[y][x] == WALL) {
        if (y > 0 && pacMap[y - 1][x] != WALL)
            --y;
        else if (y < 29 && pacMap[y + 1][x] != WALL)
            ++y;
        else if (x > 0 && pacMap[y][x - 1] != WALL)
            --x;
        else if (x < 29 && pacMap[y][x + 1] != WALL)
            ++x;
    }
    if (_position.x == 1) {
        if (_position.y == 1) {
            if (_direction == types::UP)
                return types::RIGHT;
            if (_direction == types::LEFT)
                return types::DOWN;
        }
        if (_position.y == 28) {
            if (_direction == types::DOWN)
                return types::RIGHT;
            if (_direction == types::LEFT)
                return types::UP;
        }
    } else if (_position.x == 28) {
        if (_position.y == 1) {
            if (_direction == types::UP)
                return types::LEFT;
            if (_direction == types::RIGHT)
                return types::DOWN;
        }
        if (_position.y == 28) {
            if (_direction == types::DOWN)
                return types::LEFT;
            if (_direction == types::RIGHT)
                return types::UP;
        }
    }
    if ((_position.x >= 12 && _position.x <= 14) &&
    (_position.y >= 12 && _position.y <= 14) && _mode != EATEN) {
        y = 11;
        x = 13;
    }
    if ((_position.y == 11 || _position.y == 23) &&
    (_position.x >= 12 && _position.x <= 16) &&
    (_mode == SCATTER || _mode == CHASE)) {
        if (_direction == types::LEFT)
            return types::LEFT;
        if (_direction == types::RIGHT)
            return types::RIGHT;
        if (x < _position.x)
            return types::LEFT;
        return types::RIGHT;
    }
    return getTargetDirectionCorrected(y, x);
}

/**
 * @brief Computes a mirrored position using a pivot.
 * @details Returns the position symmetric to `src` with respect to the `pivot` point.
 * Often used in ghost targeting logic, such as Inky’s behavior.
 *
 * @param src The source position to mirror.
 * @param pivot The pivot point around which the position is mirrored.
 * @return The resulting symmetric position.
 */
arcade::types::Position arcade::game::pacman::Ghost::getPivotPosition(types::Position &src,
    types::Position &pivot)
{
    return {2 * pivot.x - src.x, 2 * pivot.y - src.y};
}

/**
 * @brief Computes the Euclidean distance between two positions.
 * @details Returns the distance between `pos` and `pos2` using the standard
 * Pythagorean formula. Useful for comparing ghost proximity to targets.
 *
 * @param pos First position.
 * @param pos2 Second position.
 * @return The Euclidean distance as an integer.
 */
int arcade::game::pacman::Ghost::getDistance(types::Position &pos, types::Position &pos2)
{
    return static_cast<int>(std::sqrt(std::pow(pos.x - pos2.x, 2) +
        std::pow(pos.y - pos2.y, 2)));
}

/**
 * @brief Returns the current position of the ghost.
 * @return A reference to the ghost's current position.
 */
arcade::types::Position &arcade::game::pacman::Ghost::getPosition()
{
    return _position;
}

/**
 * @brief Returns the current behavior mode of the ghost.
 * @return The ghost's current mode (e.g., CHASE, SCATTER, FRIGHTENED, EATEN).
 */
arcade::game::pacman::GhostMode arcade::game::pacman::Ghost::getMode() const
{
    return _mode;
}

/**
 * @brief Returns the internal timer value.
 * @return The current value of the ghost's timer.
 */
size_t arcade::game::pacman::Ghost::getTimer() const
{
    return _timer;
}

/**
 * @brief Moves the ghost one tile in the given direction.
 * @details Updates both the ghost’s internal position and the position of its corresponding entity.
 * Handles tunnel wrapping on the horizontal axis (x = -1 or 30) and applies vertical map offset.
 *
 * @param target The direction in which to move the ghost.
 * @param ghost A pointer to the Entity associated with the ghost (to update its display position).
 */
void arcade::game::pacman::Ghost::move(types::Direction target, types::Entity *ghost)
{
    types::Position nextPos;

    switch (target) {
        case types::UP:
            nextPos = {_position.x, _position.y - 1};
            break;
        case types::LEFT:
            nextPos = {_position.x - 1, _position.y};
            break;
        case types::RIGHT:
            nextPos = {_position.x + 1, _position.y};
            break;
        default:
            nextPos = {_position.x, _position.y + 1};
            break;
    }
    if (nextPos.x == -1)
        nextPos.x = 29;
    else if (nextPos.x == 30)
        nextPos.x = 0;
    ghost->pos.x = nextPos.x;
    ghost->pos.y = nextPos.y + MAP_MARGIN_TOP;
    _position = {nextPos.x, nextPos.y};
}

/**
 * @brief Moves the ghost in a random valid direction (FRIGHTENED mode).
 * @details Chooses a random direction using `getRandomDirection()` and
 * applies movement accordingly. Used when the ghost is in FRIGHTENED mode.
 *
 * @param ghost A pointer to the ghost's Entity, updated with the new position.
 *
 * @see getRandomDirection()
 */
void arcade::game::pacman::Ghost::moveFrightened(types::Entity *ghost)
{
    _direction = getRandomDirection();
    move(_direction, ghost);
}

/**
 * @brief Moves the ghost toward the ghost house (EATEN mode).
 * @details Sets the ghost’s direction toward the ghost house center (tile 13,14)
 * and applies movement. Used when the ghost is returning after being eaten.
 *
 * @param ghost A pointer to the ghost's Entity, updated with the new position.
 *
 * @see getTargetDirection()
 */
void arcade::game::pacman::Ghost::moveEaten(types::Entity *ghost)
{
    _direction = getTargetDirection(14, 13);
    move(_direction, ghost);
}
