//
// Created by sevendart on 2.04.21.
//

#ifndef SIBERIANGAMEJAM_ENEMY_H
#define SIBERIANGAMEJAM_ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
    enum class AIStates {WAIT, FOLLOW};

    Enemy(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon, sf::Vector2u startPosition);

    virtual void Update() override;

    virtual void Follow();
private:
    AIStates _aiState;
    int _triggerRadius;

    sf::Vector2u FindPath();
    int CountDistance();
};


#endif //SIBERIANGAMEJAM_ENEMY_H
