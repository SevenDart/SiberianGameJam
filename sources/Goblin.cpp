//
// Created by sevendart on 2.04.21.
//

#include "../include/Goblin.h"
#include "../include/Weapon.h"
#include <memory>

Goblin::Goblin() : Enemy(1,1,1, nullptr, sf::Vector2u(1, 1)) {
    _weapon = std::make_shared<Weapon>(Weapon::MainParameter::STRENGTH,
                                       0, std::make_shared<Modificator>(Modificator(nullptr,0)), 1);
    _animations[States::IDLE].load("../resources/goblin/anim_idle_", 4);
    _animations[States::HIT].load("../resources/goblin/anim_hit_", 1);
}

Goblin::Goblin(sf::Vector2u position) : Goblin() {
    _indexPosition = position;
}
