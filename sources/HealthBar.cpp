//
// Created by sevendart on 2.04.21.
//

#include "../include/HealthBar.h"
#include "SFML/Graphics.hpp"
#include "../include/Game.h"

HealthBar::HealthBar(int maxHp, int currentHp) : _maxHP(maxHp), _currentHP(currentHp) {
    _outerRectangle = sf::RectangleShape(_outerSize);
    _outerRectangle.setPosition(_position);
    _innerRectangle = sf::RectangleShape(_innerSize);
    _innerRectangle.setPosition(_position);
    _outerRectangle.setFillColor(sf::Color::White);
    _innerRectangle.setFillColor(sf::Color(0, 122, 20));
    font.loadFromFile("../resources/fonts/VT323-Regular.ttf");
    HPtext.setFont(font);
    HPtext.setCharacterSize(28);
    HPtext.scale(sf::Vector2f(0.5,0.5));
}

void HealthBar::setCurrentHp(int currentHp) {
    _currentHP = currentHp;
    _innerSize.x = (((float)currentHp / _maxHP) * _outerSize.x) - 2;
    _innerRectangle.setSize(_innerSize);
    std::string text = std::to_string(_currentHP) + "/" + std::to_string(_maxHP);
    HPtext.setString(text);
}

void HealthBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_outerRectangle, states);
    target.draw(_innerRectangle, states);
    target.draw(HPtext, states);
}

void HealthBar::setMaxHp(int maxHp) {
    _maxHP = maxHp;
}

void HealthBar::UpdatePosition() {
    _position = Game::currentGame->GetMainWindow()->mapPixelToCoords(sf::Vector2i(0, 0), Game::currentGame->GetPlayer()->getCamera());
    _outerRectangle.setPosition(_position);
    _innerRectangle.setPosition(_position + sf::Vector2f(1, 1));
    HPtext.setPosition(_position + sf::Vector2f(30,0));
}
