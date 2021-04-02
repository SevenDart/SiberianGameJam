//
// Created by sevendart on 2.04.21.
//

#include "../include/Enemy.h"

void Enemy::Step() {
    if (_aiState == AIStates::FOLLOW) {

    }
}

Enemy::Enemy(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon, sf::Vector2u startPosition)
        : Character(strength, agility, intelligence, weapon, startPosition) {

}
