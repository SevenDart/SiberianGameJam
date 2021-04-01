//
// Created by sevendart on 2.04.21.
//

#include "../include/Modificator.h"

const std::function<void(Character)> &Modificator::getAction() const {
    return action;
}

float Modificator::getDurability() const {
    return _durability;
}

Modificator::Modificator(const std::function<void(Character)> &action, float durability) : action(action),
                                                                                           _durability(durability) {
}
