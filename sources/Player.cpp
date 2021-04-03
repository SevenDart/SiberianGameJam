//
// Created by sevendart on 2.04.21.
//

#include "../include/Player.h"
#include "../include/Game.h"


Player::~Player() {

}

void Player::UpdateSprite(float elapsedTime) {
    Character::UpdateSprite(elapsedTime);
}

void Player::Input() {

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && _isPressed[sf::Keyboard::Left]) {
        Move(_indexPosition + sf::Vector2u(-1, 0));
        _isPressed[sf::Keyboard::Left] = false;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && _isPressed[sf::Keyboard::Right]) {
        Move(_indexPosition + sf::Vector2u(1, 0));
        _isPressed[sf::Keyboard::Right] = false;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _isPressed[sf::Keyboard::Up]) {
        Move(_indexPosition + sf::Vector2u(0, -1));
        _isPressed[sf::Keyboard::Up] = false;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _isPressed[sf::Keyboard::Down]) {
        Move(_indexPosition + sf::Vector2u(0, 1));
        _isPressed[sf::Keyboard::Down] = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _isPressed[sf::Keyboard::Left] = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _isPressed[sf::Keyboard::Right] = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _isPressed[sf::Keyboard::Up] = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _isPressed[sf::Keyboard::Down] = true;
    }
}

Player::Player(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon, sf::Vector2u startPosition)
        : Character(strength, agility, intelligence,
                    weapon,startPosition) {
    _camera = sf::View(this->getPosition(), sf::Vector2f(400,300));
    Game::currentGame->getMainWindow()->setView(_camera);
    _ui = new UserInterface();
    _ui->getHealthBar()->setMaxHp(this->_healthPoints);
    _ui->getHealthBar()->setCurrentHp(this->_healthPoints);

    _animations[States::IDLE].load("../resources/dude/anim_idle_", 4);
    _animations[States::HIT].load("../resources/dude/anim_hit_", 1);

    _isPressed[sf::Keyboard::Down] = false;
    _isPressed[sf::Keyboard::Up] = false;
    _isPressed[sf::Keyboard::Left] = false;
    _isPressed[sf::Keyboard::Right] = false;
}

void Player::GetDamage(int damage) {
    Character::GetDamage(damage);
    _ui->getHealthBar()->setCurrentHp(this->_healthPoints);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Character::draw(target, states);
    target.draw(*_ui, states);
}

const sf::View &Player::getCamera() const {
    return _camera;
}

void Player::Move(sf::Vector2u newPosition) {
    Character::Move(newPosition);
    _camera.setCenter(this->getPosition());
    _ui->getHealthBar()->UpdatePosition();
    Game::currentGame->UpdateCharacters();
}

void Player::Update() {
}
