/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanGame
*/

/**
 * @file PacmanGame.cpp
 * @brief Implements the Main class of the Pacman game.
 * @author Jason Koenig
 * @version 1.0
 * @date 2025-04-14
 *
 * @details
 * Contains the entire game loop, which is managed by the update function.
 *
 * @see arcade::game::PacmanGame
 */
#include "PacmanGame.hpp"

 /**
 * @brief Loads the best score stored in binary form in the file Score/pacman.dat.
 **/
void arcade::game::PacmanGame::loadHighScore()
{
    std::ifstream file("Score/pacman.dat", std::ios::binary);

    if (!file || !file.is_open()) {
        _highScore = 0;
        return;
    }
    file.read(reinterpret_cast<char *>(&_highScore), sizeof(_highScore));
    if (file.gcount() != sizeof(_highScore))
        _highScore = 0;
    file.close();
}

 /**
 * @brief Stores the best score achieved in binary format in the file Score/pacman.dat.
 **/
void arcade::game::PacmanGame::saveHighScore()
{
    std::ofstream file("Score/pacman.dat", std::ios::binary | std::ios::trunc);

    if (!file || !file.is_open())
        return;
    file.write(reinterpret_cast<char *>(&_highScore), sizeof(_highScore));
    file.close();
}

 /**
 * @brief Updates level, score and highscore display.
 **/
void arcade::game::PacmanGame::refreshScore()
{
    types::Entity *scoreTxt = getEntityAt((types::Position){2, 2});

    if (_score > _highScore)
        _highScore = _score;
    if (scoreTxt)
        scoreTxt->str = "level " + std::to_string(_level) +
        "   score " + std::to_string(_score) +
        "   high score " + std::to_string(_highScore);
}

/**
 * @brief Updates the state of a specific ghost (collision with player, mode switch).
 * @param ghost The ghost to update (Blinky, Inky, Pinky or Clyde).
 * @param playerPos The current position of the player (Pacman).
 * @return true if the ghost collided with the player and caused a state change (death or kill), false otherwise.
 **/
bool arcade::game::PacmanGame::updateGhost(pacman::Ghost &ghost,
    types::Position &playerPos)
{
    types::Position &ghostPos = ghost.getPosition();
    pacman::GhostMode ghostMode = ghost.getMode();

    exitGhostSpecialModes(ghost);
    if (ghostPos == playerPos) {
        if (ghostMode == pacman::FRIGHTENED) {
            int killRow = _player.getKillRow() + 1;

            _score += getFoodValue(ghost.getId());
            _player.setKillRow(killRow);
            setGhostSkin(ghost.getId(), pacman::DEAD);
            ghost.setMode(pacman::EATEN);
        }
        if (ghostMode < pacman::FRIGHTENED) {
            int remainingLives = _player.getExtraLifes();

            if (remainingLives == 0) {
                setGameOver(true);
                return true;
            }
            _player.setExtraLifes(remainingLives - 1);
            _dotCpt = 0;
            removeEntityAtByChar(pacman::LIFE);
            resetGameEntities();
            return true;
        }
    }
    if (ghostMode == pacman::FRIGHTENED && _timer % (getCycleTime() * 2) != 0)
        return true;
    return false;
}

/**
 * @brief Updates all ghosts’ movement and state.
 * @details
 * Each ghost checks whether it should move or change state.
 * Ghost movement depends on player position, direction, and current level.
 * Certain ghosts (Inky, Clyde) are unlocked progressively based on the number of dots eaten.
 */
void arcade::game::PacmanGame::updateGhosts()
{
    types::Direction playerDirection = _player.getDirection();
    types::Position &playerPos = _player.getPos();

    if (!updateGhost(_blinky, playerPos))
        _blinky.update(getEntityAtByChar(pacman::BLINKY), playerPos);
    if (!updateGhost(_pinky, playerPos))
        _pinky.update(getEntityAtByChar(pacman::PINKY), playerPos, playerDirection);
    if (!updateGhost(_inky, playerPos) && (_level > 1 || _dotCpt >= 30))
        _inky.update(getEntityAtByChar(pacman::INKY), playerPos,
        _blinky.getPosition(), playerDirection);
    if (!updateGhost(_clyde, playerPos) &&
    (_level > 2 || (_level > 1 && _dotCpt >= 50) || _dotCpt >= 60))
        _clyde.update(getEntityAtByChar(pacman::CLYDE), playerPos);
}

/**
 * @brief Main game loop entrypoint for Pacman.
 * @param event The current input event (usually a direction from the player).
 * @details
 * Handles timing, movement, food collection, level transitions and ghost logic.
 * Updates map state and entities accordingly.
 * 
 * @see updateGhosts(), updateGhost(), refreshScore()
 */
void arcade::game::PacmanGame::update(GameEvent event)
{
    _player.updateDirection(event.second);

    ++_timer;
    if (_timer % getCycleTime() != 0)
        return;
    ++_fruitTimer;
    if (_fruitTimer % (TIME_1_SEC * 10) == 0) {
        types::Entity *entity = getEntityAt(_playerStartPos);

        if (entity && entity->type == types::FOOD)
            removeEntityAt(_playerStartPos);
    }

    types::Position nextPos = _player.getNextPos();
    types::Position nextScreenPos = {nextPos.x, nextPos.y + MAP_MARGIN_TOP};
    types::Entity *nextPosEntity = getEntityAt(nextScreenPos);

    if (nextPosEntity) {
        if (!(nextPosEntity->type == types::FOOD ||
        nextPosEntity->type == types::ENEMY || nextPosEntity->type == types::EMPTY)) {
            updateGhosts();
            return;
        }
        if (nextPosEntity->type == types::FOOD) {
            _score += getFoodValue(nextPosEntity->display_char);
            refreshScore();
            if (_remainingDots == 70 || _remainingDots == 170) {
                generateFood();
            } else if (_remainingDots == 0) {
                ++_level;
                refreshScore();
                removeEntityAt(nextScreenPos);
                removeEntityAtByChar(pacman::BLINKY);
                removeEntityAtByChar(pacman::PINKY);
                removeEntityAtByChar(pacman::INKY);
                removeEntityAtByChar(pacman::CLYDE);
                removeEntityAtByChar(pacman::PAC);
                initGameMap();
                initGameEntities();
                return;
            }
        }
        if (nextPosEntity->type != types::ENEMY)
            removeEntityAt(nextScreenPos);
    }
    _player.move(nextPos.y, nextPos.x, getEntityAt(_player.getRealPos()));
    updateGhosts();
}
