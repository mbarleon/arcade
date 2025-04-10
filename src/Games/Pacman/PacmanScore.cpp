/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanScore
*/

#include "PacmanGame.hpp"

int arcade::game::PacmanGame::getFoodValue(char food)
{
    switch (food) {
        case GUM:
            return 10;
        case GUM2:
            return 50;
        case APPLE:
            return 200;
        case BANANA:
            return 500;
        case CHERRIES:
            return 800;
        case PINEAPPLE:
            return 1500;
        case POTION:
            return 3000;
        case KEY:
            return 5000;
        default:
            break;
    }
    if (food != PINKY && food != CLYDE &&
    food != BLINKY && food != INKY)
        return 0;
    switch (_ghostKillRow) {
        case 0:
            return 200;
        case 1:
            return 400;
        case 2:
            return 800;
        default:
            return 1600;
    }
}

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
    types::Entity *highScoreTxt;

    if (scoreTxt)
        scoreTxt->str = "score : " + std::to_string(_score);
    if (_score > _highScore) {
        _highScore = _score;
        highScoreTxt = getEntityAt((types::Position){15, 2});
        highScoreTxt->str = "high score : " + std::to_string(_highScore);
    }
}
