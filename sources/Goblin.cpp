//
// Created by sevendart on 2.04.21.
//

#include "../include/Goblin.h"
#include "../include/Weapon.h"
#include <memory>

Goblin::Goblin() : Enemy(1,1,1, nullptr, sf::Vector2u(1, 1)) {
    _weapon = std::make_shared<Weapon>(Weapon::MainParameter::STRENGTH, 1, nullptr, 1);
}

Goblin::Goblin(sf::Vector2u position) : Goblin() {
    _indexPosition = position;
}
