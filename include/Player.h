//
// Created by sevendart on 2.04.21.
//

#ifndef SIBERIANGAMEJAM_PLAYER_H
#define SIBERIANGAMEJAM_PLAYER_H

#include "SFML/Graphics.hpp"
#include "Character.h"

class Player : public Character {
private:
    sf::View _camera;
    ~Player() override;
public:
    Player(int strength, int agility, int intelligence);
    void UpdateSprite(float elapsedTime) override;
    void Update() override;
    void Input();
};


#endif //SIBERIANGAMEJAM_PLAYER_H
