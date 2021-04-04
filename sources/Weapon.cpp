//
// Created by sevendart on 2.04.21.
//

#include "../include/Weapon.h"
#include "../include/Game.h"

int Weapon::CalculateDamage(int strength, int agility, int intelligence) {
    int mainPoints;
    switch (_mainParameter) {
        case MainParameter::STRENGTH:
            mainPoints = strength;
            break;
        case MainParameter::AGILITY:
            mainPoints = agility;
            break;
        case MainParameter::INTELLIGENCE:
            mainPoints = intelligence;
            break;
    }
    int result = (int)(_damage * (1 + ((float)mainPoints / 20)));
    if (Game::CheckChance(intelligence))
        result *= 2;
    return result;
}

Weapon::Weapon(MainParameter mainParameter, int damage, std::shared_ptr<Modificator> attackModificator, int distance)
        : _mainParameter(mainParameter), _damage(damage), _attackModificator(*attackModificator), _distance(distance) {

}

Modificator Weapon::getAttackModificator() const {
    return _attackModificator;
}

int Weapon::GetDistance() const {
    return _distance;
}

int Weapon::Upgrade() {
    return _damage++;
}

