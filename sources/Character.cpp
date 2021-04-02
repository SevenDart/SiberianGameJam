//
// Created by sevendart on 2.04.21.
//

#include "../include/Character.h"
#include "../include/Game.h"
#include "../include/Modificator.h"
#include "../include/Weapon.h"

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

Character::Character(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon) : _strength(strength), _agility(agility),
                                                                                                    _intelligence(intelligence),
                                                                                                    _weapon(weapon) {
    _healthPoints = HEALTH_PER_POINT * strength;
}

void Character::Attack(Character character) {
    character.GetDamage(_weapon->CalculateDamage(_strength, _agility, _intelligence));
    if (_weapon->getAttackModificator().getAction() != nullptr) character.GetModificator(_weapon->getAttackModificator());
}

void Character::GetModificator(Modificator modificator) {
    _modificators.push_back(std::shared_ptr<Modificator>(&modificator));
}


Character::~Character() = default;
