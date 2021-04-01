//
// Created by sevendart on 2.04.21.
//
#ifndef SIBERIANGAMEJAM_MODIFICATOR_H
#define SIBERIANGAMEJAM_MODIFICATOR_H

#include "SFML/Graphics.hpp"
#include "Character.h"
#include <memory>
#include <functional>

class Modificator {
private:
    std::function<void(std::shared_ptr<Character>)> action;
    int _durability;
public:
    const std::function<void(std::shared_ptr<Character>)> &getAction() const;
    int getDurability() const;
    Modificator(const std::function<void(std::shared_ptr<Character>)> &action, int durability);
};


#endif //SIBERIANGAMEJAM_MODIFICATOR_H
