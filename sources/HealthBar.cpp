//
// Created by sevendart on 2.04.21.
//

#include "../include/HealthBar.h"
#include "SFML/Graphics.hpp"

HealthBar::HealthBar(int maxHp, int currentHp) : _maxHP(maxHp), _currentHP(currentHp) {
    _outerRectangle = sf::RectangleShape(_outerSize);
    _outerRectangle.setPosition(_position);
    _innerRectangle = sf::RectangleShape(_innerSize);
    _innerRectangle.setPosition(_position);
    _outerRectangle.setFillColor(sf::Color::Black);
    _innerRectangle.setFillColor(sf::Color::Green);
}

void HealthBar::setCurrentHp(int currentHp) {
    _currentHP = currentHp;
    _innerSize.x = (((float)currentHp / _maxHP) * _outerSize.x);
    _innerRectangle.setSize(_innerSize);
}

void HealthBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_outerRectangle, states);
    target.draw(_innerRectangle, states);
}

void HealthBar::setMaxHp(int maxHp) {
    _maxHP = maxHp;
}
