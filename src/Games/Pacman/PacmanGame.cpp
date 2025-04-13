/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanGame
*/

#include "PacmanGame.hpp"

void arcade::game::PacmanGame::loadHighScore()
{
    std::ifstream file("Score/PacmanGame.arcade");

    if (!file || !file.is_open()) {
        _highScore = 0;
        return;
    }
    if (!(file >> _highScore))
        _highScore = 0;
    file.close();
}

void arcade::game::PacmanGame::saveHighScore()
{
    std::ofstream file("Score/PacmanGame.arcade", std::ios::trunc);

    if (!file || !file.is_open())
        return;
    file << _highScore;    
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
    int remainingLives = _player.getExtraLifes();

    if (_blinky.getPosition() == playerPos || _pinky.getPosition() == playerPos ||
    _inky.getPosition() == playerPos || _clyde.getPosition() == playerPos) {
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
    ++_fruitTimer;
    if (_timer % 6 != 0)
        return;
    _timer = 0;
    if (_fruitTimer % 720 == 0) {
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
