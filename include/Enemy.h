//
// Created by sevendart on 2.04.21.
//

#ifndef SIBERIANGAMEJAM_ENEMY_H
#define SIBERIANGAMEJAM_ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
    void Step();
    enum class AIStates {WAIT, FOLLOW};
private:
    AIStates _aiState;
};


#endif //SIBERIANGAMEJAM_ENEMY_H