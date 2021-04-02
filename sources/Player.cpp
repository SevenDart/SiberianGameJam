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
    _ui = new UserInterface();
    _ui->getHealthBar()->setMaxHp(this->_healthPoints);
    _ui->getHealthBar()->setCurrentHp(this->_healthPoints);
}

void Player::GetDamage(int damage) {
    Character::GetDamage(damage);
    _ui->getHealthBar()->setCurrentHp(this->_healthPoints);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Character::draw(target, states);
    target.draw(*_ui, states);
}
