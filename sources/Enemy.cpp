//
// Created by sevendart on 2.04.21.
//

#include "../include/Enemy.h"
#include "../include/Game.h"
#include "../include/Weapon.h"
#include <cmath>
#include <queue>

void Enemy::Update() {
    Character::Update();
    if (CountDistance() <= _triggerRadius)
        _aiState = AIStates::FOLLOW;
    if (_aiState == AIStates::FOLLOW) {
        Follow();
    }
}

Enemy::Enemy(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon, sf::Vector2u startPosition)
        : Character(strength, agility, intelligence, weapon, startPosition) {
    _triggerRadius = 10;
    _aiState = AIStates::WAIT;
}


void Enemy::Follow() {
    if (CountDistance() <= _weapon->GetDistance()) {
        Attack(Game::currentGame->GetPlayer());
    }
    else {
        sf::Vector2u step = FindPath();
        sf::Vector2u newPos = _indexPosition - step;
        if (Level::currentLevel->GetCells()[newPos.y][newPos.x].character == nullptr) Move(_indexPosition - step);
    }
}

int Enemy::CountDistance() {
    sf::Vector2u playerPosition = Game::currentGame->GetPlayer()->GetIndexPosition();
    return abs((int)_indexPosition.x - (int)playerPosition.x) + abs((int)_indexPosition.y - (int)playerPosition.y);
}

sf::Vector2u Enemy::FindPath() {
    CellMatrix map = Level::currentLevel->GetCells();
    std::vector<std::vector<int>> pathMap;
    pathMap.resize(map.size());
    for (int i = 0; i < pathMap.size(); i++) {
        pathMap[i].resize(map[i].size());
        for (int j = 0; j < pathMap[i].size(); j++)
            if (!map[i][j].isReachable) pathMap[i][j] = -1;
    }

    sf::Vector2u playerPosition = Game::currentGame->GetPlayer()->GetIndexPosition();

    std::queue<sf::Vector2u> coords;
    coords.push(_indexPosition);
    pathMap[_indexPosition.y][_indexPosition.x] = -2;
    int step = 1;
    while (!coords.empty()) {
        int length = coords.size();
        for (int i = 0; i < length; i++) {
            sf::Vector2u currentPosition = coords.front();
            if (pathMap[currentPosition.y + 1][currentPosition.x] == 0) {
                pathMap[currentPosition.y + 1][currentPosition.x] = step;
                coords.push(currentPosition + sf::Vector2u(0, 1));
            }
            if (pathMap[currentPosition.y - 1][currentPosition.x] == 0) {
                pathMap[currentPosition.y - 1][currentPosition.x] = step;
                coords.push(currentPosition + sf::Vector2u(0, -1));
            }
            if (pathMap[currentPosition.y][currentPosition.x - 1] == 0) {
                pathMap[currentPosition.y][currentPosition.x - 1] = step;
                coords.push(currentPosition + sf::Vector2u(-1, 0));
            }
            if (pathMap[currentPosition.y][currentPosition.x + 1] == 0) {
                pathMap[currentPosition.y][currentPosition.x + 1] = step;
                coords.push(currentPosition + sf::Vector2u(1, 0));
            }
            coords.pop();
        }
        if (pathMap[playerPosition.y][playerPosition.x] != 0)
            break;
        step++;
    }

    if (pathMap[playerPosition.y][playerPosition.x] == 0) {
        _aiState = AIStates::WAIT;
        return sf::Vector2u(0,0);
    }

    pathMap[_indexPosition.y][_indexPosition.x] = 0;

    sf::Vector2u lastPosition;
    sf::Vector2u currentPosition(playerPosition);
    while (currentPosition != _indexPosition) {
        if (pathMap[currentPosition.y][currentPosition.x] - pathMap[currentPosition.y + 1][currentPosition.x] == 1) {
            lastPosition = currentPosition;
            currentPosition.y += 1;
        }
        if (pathMap[currentPosition.y][currentPosition.x] - pathMap[currentPosition.y - 1][currentPosition.x] == 1) {
            lastPosition = currentPosition;
            currentPosition.y -= 1;
        }
        if (pathMap[currentPosition.y][currentPosition.x] - pathMap[currentPosition.y][currentPosition.x + 1] == 1) {
            lastPosition = currentPosition;
            currentPosition.x += 1;
        }
        if (pathMap[currentPosition.y][currentPosition.x] - pathMap[currentPosition.y][currentPosition.x - 1] == 1) {
            lastPosition = currentPosition;
            currentPosition.x -= 1;
        }
    }

    return _indexPosition - lastPosition;
}
