//
// Created by sevendart on 2.04.21.
//

#ifndef SIBERIANGAMEJAM_PLAYER_H
#define SIBERIANGAMEJAM_PLAYER_H

#include "SFML/Graphics.hpp"
#include "Character.h"

class Player : public Character {
private:
    int _goldAmount;

    sf::View _camera;
    ~Player() override;
public:
    void Update(float elapsedTime) override;
};


#endif //SIBERIANGAMEJAM_PLAYER_H
