//
// Created by sevendart on 2.04.21.
//

#include "../include/Modificator.h"


int Modificator::DecDurability() const {
    return _durability;
}

Modificator::Modificator(const std::function<void(std::shared_ptr<Character>)> &action, int durability) {
    _durability = durability;
    this->action = action;
}

const std::function<void(std::shared_ptr<Character>)> &Modificator::getAction() const {
    return action;
}

