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

    if (scoreTxt)
        scoreTxt->str = "score : " + std::to_string(_score) +
        "     high score : " + std::to_string(_highScore);
}

void arcade::game::PacmanGame::updateGhosts()
{
    types::Direction playerDirection = _player.getDirection();
    types::Position &playerPos = _player.getPos();

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

    updateGhosts();

    types::Position nextPos = _player.getNextPos();
    types::Position nextScreenPos = {nextPos.x, nextPos.y + MAP_MARGIN_TOP};
    types::Entity *nextPosEntity = getEntityAt(nextScreenPos);

    if (nextPosEntity) {
        if (!(nextPosEntity->type == types::FOOD ||
        nextPosEntity->type == types::ENEMY || nextPosEntity->type == types::EMPTY))
            return;
        if (nextPosEntity->type == types::ENEMY) {
            int remainingLives = _player.getExtraLifes();
            if (remainingLives == 0) {
                setGameOver(true);
                return;   
            }
            _player.setExtraLifes(remainingLives);
            _dotCpt = 0;
            removeGameEntities();
            initGameEntities();
            return;
        }
        if (nextPosEntity->type == types::FOOD) {
            _score += getFoodValue(nextPosEntity->display_char);
            refreshScore();
        }
        removeEntityAt(nextScreenPos);
    } else if (pacman::pacMap[nextPos.y][nextPos.x] == pacman::WALL)
        return;
    _player.move(nextPos.y, nextPos.x, getEntityAt(_player.getRealPos()));
}
