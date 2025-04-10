/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanGame
*/

#include "PacmanGame.hpp"

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
