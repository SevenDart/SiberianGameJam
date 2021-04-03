//
// Created by sevendart on 2.04.21.
//

#ifndef SIBERIANGAMEJAM_ENEMY_H
#define SIBERIANGAMEJAM_ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
    Enemy(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon, sf::Vector2u startPosition);

    void Step();
    enum class AIStates {WAIT, FOLLOW};
private:
    AIStates _aiState;
};


#endif //SIBERIANGAMEJAM_ENEMY_H
