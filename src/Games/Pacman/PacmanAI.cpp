/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** PacmanAI
*/

#include "PacmanGame.hpp"

void arcade::game::PacmanGame::populateTargetMapPos(int y, int x, int sum)
{
    if (y == 14) {
        if (x == -1)
            x = 29;
        if (x == 30)
            x = 0;
    }
    if (y < 0 || x < 0 || y > 29 || x > 29 ||
    _pacMap[y][x] == 'X')
        return;
    if (_targetMap[y][x] == -1 || sum < _targetMap[y][x]) {
        _targetMap[y][x] = sum;
        populateTargetMapPos(y - 1, x, sum + 1);
        populateTargetMapPos(y + 1, x, sum + 1);
        populateTargetMapPos(y, x + 1, sum + 1);
        populateTargetMapPos(y, x - 1, sum + 1);
    }
}

arcade::types::Direction arcade::game::PacmanGame::populateTargetMap(types::Position &mapGhostPos,
    types::Position &mapTargetPos)
{
    int directions[4];

    initGameTargetMap();
    _targetMap[mapGhostPos.y][mapGhostPos.x] = -2;
    _targetMap[mapTargetPos.y][mapTargetPos.x] = 0;

    populateTargetMapPos(mapTargetPos.y - 1, mapTargetPos.x, 1);
    populateTargetMapPos(mapTargetPos.y + 1, mapTargetPos.x, 1);
    populateTargetMapPos(mapTargetPos.y, mapTargetPos.x + 1, 1);
    populateTargetMapPos(mapTargetPos.y, mapTargetPos.x - 1, 1);

    if (mapTargetPos.y == 14) {
        switch (mapTargetPos.x) {
            case 0:
                directions[types::LEFT] = _targetMap[mapGhostPos.y][29];
                directions[types::RIGHT] = _targetMap[mapGhostPos.y][mapGhostPos.x + 1];
                break;
            case 29:
                directions[types::LEFT] = _targetMap[mapGhostPos.y][mapGhostPos.x - 1];
                directions[types::RIGHT] = _targetMap[mapGhostPos.y][0];
                break;
            default:
                directions[types::LEFT] = _targetMap[mapGhostPos.y][mapGhostPos.x - 1];
                directions[types::RIGHT] = _targetMap[mapGhostPos.y][mapGhostPos.x + 1];
                break;
        }
    }
    directions[types::UP] = _targetMap[mapGhostPos.y - 1][mapGhostPos.x];
    directions[types::DOWN] = _targetMap[mapGhostPos.y + 1][mapGhostPos.x];

    if (directions[types::RIGHT] != -1 &&
    (directions[types::RIGHT] < directions[types::DOWN] || directions[types::DOWN] == -1) &&
    (directions[types::RIGHT] < directions[types::LEFT] || directions[types::LEFT] == -1) &&
    (directions[types::RIGHT] < directions[types::UP] || directions[types::UP] == -1))
        return types::RIGHT;
    if (directions[types::DOWN] != -1 &&
    (directions[types::DOWN] < directions[types::RIGHT] || directions[types::RIGHT] == -1) &&
    (directions[types::DOWN] < directions[types::LEFT] || directions[types::LEFT] == -1) &&
    (directions[types::DOWN] < directions[types::UP] || directions[types::UP] == -1))
        return types::DOWN;
    if (directions[types::LEFT] != -1 &&
    (directions[types::LEFT] < directions[types::RIGHT] || directions[types::RIGHT] == -1) &&
    (directions[types::LEFT] < directions[types::DOWN] || directions[types::DOWN] == -1) &&
    (directions[types::LEFT] < directions[types::UP] || directions[types::UP] == -1))
        return types::LEFT;
    return types::UP;
}
