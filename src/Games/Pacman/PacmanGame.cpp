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

void arcade::game::PacmanGame::update(GameEvent event)
{
    player.updateDirection(event.second);

    ++_timer;
    if (_timer % 6 != 0)
        return;
    _timer = 0;

    types::Position nextPos = player.getNextPos();
    types::Position nextScreenPos = {nextPos.x, nextPos.y + MAP_MARGIN_TOP};
    types::Entity *nextPosEntity = getEntityAt(nextScreenPos);

    if (nextPosEntity) {
        if (!(nextPosEntity->type == types::FOOD ||
        nextPosEntity->type == types::ENEMY || nextPosEntity->type == types::EMPTY))
            return;
        if (nextPosEntity->type == types::ENEMY) {
            int remainingLives = player.getExtraLifes();
            if (remainingLives == 0) {
                setGameOver(true);
                return;   
            }
            player.setExtraLifes(remainingLives);
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
    player.move(nextPos.y, nextPos.x, getEntityAt(player.getRealPos()));
}
