/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanGame
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

void arcade::game::PacmanGame::refreshScore()
{
    types::Entity *score_txt = getEntityAt((types::Position){2, 2});

    if (score_txt)
        score_txt->str = "score : " + std::to_string(_score);
}

void arcade::game::PacmanGame::update(GameEvent event)
{
    updateDirection(event.second);

    ++_timer;
    if (_timer < 6)
        return;
    _timer = 0;

    types::Position targetPos = getNextCasePos();
    types::Position targetScreenPos = {targetPos.x, targetPos.y + MAP_MARGIN_TOP};
    types::Entity *target = getEntityAt(targetScreenPos);

    if (target) {
        if (!(target->type == types::FOOD ||
        target->type == types::ENEMY || target->type == types::EMPTY))
            return;
        if (target->type == types::ENEMY) {
            if (_extraLifes == 0)
                setGameOver(true);
            --_extraLifes;
            removeGameEntities();
            initGameEntities();
            return;
        }
        if (target->type == types::FOOD) {
            _score += getFoodValue(target->display_char);
            refreshScore();
        }
        removeEntityAt(targetScreenPos);
    } else if (_pacMap[targetPos.y][targetPos.x] == 'X')
        return;
    movePlayer(targetPos.y, targetPos.x);
}
