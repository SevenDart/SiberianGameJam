//
// Created by slonik on 4/4/21.
//


#include "../include/Dwarf.h"
#include "../include/Weapon.h"

Dwarf::Dwarf() : Enemy(1,1,2, nullptr, sf::Vector2u(1, 1)) {
    _weapon = std::make_shared<Weapon>(Weapon::MainParameter::INTELLIGENCE,
                                       1, std::make_shared<Modificator>(Modificator(nullptr,0)), 1);
    _animations[States::IDLE].load("../resources/dwarf/anim_idle_", 4);
    _animations[States::HIT].load("../resources/dwarf/anim_hit_", 1);
}

Dwarf::Dwarf(sf::Vector2u position) : Dwarf() {
    _indexPosition = position;
}

