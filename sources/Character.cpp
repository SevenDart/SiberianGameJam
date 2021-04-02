//
// Created by sevendart on 2.04.21.
//

#include "../include/Character.h"
#include "../include/Game.h"
#include "../include/Modificator.h"

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

void Character::Update() {
    for (auto it = _modificators.begin(); it != _modificators.end(); it++) {
        (*it)->getAction()(std::shared_ptr<Character>(this));
        if ((*it)->DecDurability() == 0) {
            _modificators.erase(it);
        }
    }
}

void Character::UpdateSprite(float elapsedTime) {
    _sprite.setTexture(_animations[_currentState].nextFrame(elapsedTime));
    _sprite.setPosition(this->getPosition());
}


void Character::GetDamage(int damage) {
    _currentState = States::HIT;
    if (Game::CheckChance(_agility))
        return;
    _healthPoints -= damage;
    if (damage < 0)
        delete this;
}

Character::Character(int strength, int agility, int intelligence) : _strength(strength), _agility(agility),
                                                                    _intelligence(intelligence) {
    _healthPoints = HEALTH_PER_POINT * strength;
}


Character::~Character() = default;
