//
// Created by sevendart on 2.04.21.
//

#include "../include/UserInterface.h"

void UserInterface::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*_healthBar, states);
}

UserInterface::UserInterface() {
    _healthBar = new HealthBar(5,5);
}

HealthBar *UserInterface::getHealthBar() const {
    return _healthBar;
}
