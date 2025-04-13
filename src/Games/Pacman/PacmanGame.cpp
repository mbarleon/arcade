/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanGame
*/

#include "PacmanGame.hpp"

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

void arcade::game::PacmanGame::saveHighScore()
{
    std::ofstream file("Score/pacman.dat", std::ios::binary | std::ios::trunc);

    if (!file || !file.is_open())
        return;
    file.write(reinterpret_cast<char *>(&_highScore), sizeof(_highScore));
    file.close();
}

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

void arcade::game::PacmanGame::updateGhosts()
{
    types::Direction playerDirection = _player.getDirection();
    types::Position &playerPos = _player.getPos();
    types::Position &blinkyPos = _blinky.getPosition();
    types::Position &pinkyPos = _pinky.getPosition();
    types::Position &inkyPos = _inky.getPosition();
    types::Position &clydePos = _clyde.getPosition();
    int remainingLives = _player.getExtraLifes();

    if ((blinkyPos == playerPos && _blinky.getMode() == pacman::FRIGHTENED) ||
    (pinkyPos == playerPos && _pinky.getMode() == pacman::FRIGHTENED) ||
    (inkyPos == playerPos && _inky.getMode() == pacman::FRIGHTENED) ||
    (clydePos == playerPos && _clyde.getMode() == pacman::FRIGHTENED)) {
        int playerKillRow = _player.getKillRow() + 1;

        _score += getFoodValue(pacman::BLINKY);
        _player.setKillRow(playerKillRow);
        if (blinkyPos == playerPos)
            _blinky.setMode(pacman::EATEN);
        if (pinkyPos == playerPos)
            _pinky.setMode(pacman::EATEN);
        if (inkyPos == playerPos)
            _inky.setMode(pacman::EATEN);
        if (clydePos == playerPos)
            _clyde.setMode(pacman::EATEN);
    }

    if ((blinkyPos == playerPos && _blinky.getMode() < pacman::FRIGHTENED) ||
    (pinkyPos == playerPos && _pinky.getMode() < pacman::FRIGHTENED) ||
    (inkyPos == playerPos && _inky.getMode() < pacman::FRIGHTENED) ||
    (clydePos == playerPos && _clyde.getMode() < pacman::FRIGHTENED)) {
        if (remainingLives == 0) {
            setGameOver(true);
            return;
        }
        _player.setExtraLifes(remainingLives - 1);
        _dotCpt = 0;
        removeEntityAtByChar(pacman::LIFE);
        resetGameEntities();
        return;
    }

    _blinky.update(getEntityAtByChar(pacman::BLINKY), playerPos);
    _pinky.update(getEntityAtByChar(pacman::PINKY), playerPos, playerDirection);
    if (_level > 1 || _dotCpt >= 30)
        _inky.update(getEntityAtByChar(pacman::INKY), playerPos,
        _blinky.getPosition(), playerDirection);
    if (_level > 2 || (_level > 1 && _dotCpt >= 50) || _dotCpt >= 60)
        _clyde.update(getEntityAtByChar(pacman::CLYDE), playerPos);
}

void arcade::game::PacmanGame::update(GameEvent event)
{
    _player.updateDirection(event.second);

    ++_timer;
    if (_timer % 6 != 0)
        return;
    _timer = 0;
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
