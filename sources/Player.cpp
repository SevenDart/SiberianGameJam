//
// Created by sevendart on 2.04.21.
//

#include "../include/Player.h"

void Player::Update() {
    Character::Update();
}



Player::~Player() {

}

void Player::UpdateSprite(float elapsedTime) {
    Character::UpdateSprite(elapsedTime);
}

void Player::Input() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

    }
}

Player::Player(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon) : Character(strength, agility, intelligence,
                                                                        weapon) {

}
