//
// Created by sevendart on 2.04.21.
//

#ifndef SIBERIANGAMEJAM_WEAPON_H
#define SIBERIANGAMEJAM_WEAPON_H

#include "Character.h"
#include "Modificator.h"


class Weapon {
public:
    enum class MainParameter {STRENGTH, AGILITY, INTELLIGENCE};
    Weapon(MainParameter mainParameter, int damage, std::shared_ptr<Modificator> attackModificator, int distance);
    virtual int CalculateDamage(int strength, int agility, int intelligence);
    Modificator getAttackModificator() const;

    int GetDistance() const;

    int Upgrade();

private:
    MainParameter _mainParameter;
    int _damage;
    int _distance;
    Modificator _attackModificator;
};


#endif //SIBERIANGAMEJAM_WEAPON_H
