//
// Created by sevendart on 2.04.21.
//
#ifndef SIBERIANGAMEJAM_MODIFICATOR_H
#define SIBERIANGAMEJAM_MODIFICATOR_H

#include "SFML/Graphics.hpp"
#include "Character.h"

class Modificator {
private:
    std::function<void(std::shared_ptr<Character>)> action;
    float _durability;
public:
    const std::function<void(std::shared_ptr<Character>)> &getAction() const;
    float getDurability() const;
    Modificator(const std::function<void(std::shared_ptr<Character>)> &action, float durability);
};


#endif //SIBERIANGAMEJAM_MODIFICATOR_H
