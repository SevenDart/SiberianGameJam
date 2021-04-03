//
// Created by sevendart on 2.04.21.
//

#include "../include/Character.h"
#include "../include/Game.h"
#include "../include/Weapon.h"
#include <cmath>
#include <iostream>
#include <utility>

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
    if (_animations[_currentState].isFinished && _currentState == States::HIT) _currentState = States::IDLE;
    _sprite.setPosition(this->getPosition());
}


void Character::GetDamage(int damage) {
    SetCurrentState(States::HIT);
    if (Game::CheckChance(_agility))
        return;
    _healthPoints -= damage;
    if (damage < 0)
        delete this;
}

Character::Character(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon,
                     sf::Vector2u startPosition) :
    _strength(strength), _agility(agility),
    _intelligence(intelligence), _weapon(std::move(weapon)), _indexPosition(startPosition)
    {
        _healthPoints = HEALTH_PER_POINT * strength;
        SetCurrentState(States::IDLE);
        _gold = 0;
}

void Character::Attack(Character* character) {
    character->GetDamage(_weapon->CalculateDamage(_strength, _agility, _intelligence));
    if (_weapon->getAttackModificator().getAction() != nullptr)
        character->GetModificator(_weapon->getAttackModificator());
}

void Character::GetModificator(Modificator modificator) {
    _modificators.push_back(std::shared_ptr<Modificator>(&modificator));
}

void Character::Move(sf::Vector2u newPosition) {
    CellMatrix map = Level::currentLevel->GetCells();
    if (newPosition == _indexPosition) return;
    if (map[newPosition.y][newPosition.x].isReachable && map[newPosition.y][newPosition.x].character == nullptr) {
        Level::currentLevel->GetCells()[newPosition.y][newPosition.x].character =
                std::move(Level::currentLevel->GetCells()[_indexPosition.y][_indexPosition.x].character);
        this->setPosition(Level::currentLevel->TILE_SIZE.x * newPosition.x + 4,
                          Level::currentLevel->TILE_SIZE.y * newPosition.y - 4);
        _indexPosition = newPosition;
    }
}

const sf::Vector2u &Character::GetIndexPosition() const {
    return _indexPosition;
}

void Character::SetCurrentState(Character::States newState) {
    if (newState != _currentState) _animations[newState].reset();
    _currentState = newState;
}


Character::~Character() = default;
