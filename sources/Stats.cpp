//
// Created by sevendart on 4.04.21.
//

#include "../include/Stats.h"
#include "../include/Game.h"
#include "../include/Weapon.h"

void Stats::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_background,states);
    target.draw(_parameters, states);
    target.draw(_weapon, states);
}

void Stats::UpdateParameters() {
    _strength = Game::currentGame->GetPlayer()->GetStrength();
    _agility = Game::currentGame->GetPlayer()->GetAgility();
    _intelligence = Game::currentGame->GetPlayer()->GetIntelligence();
    _parametersString = "strength:" + std::to_string(_strength) + " agility:" + std::to_string(_agility) + " Intelligence:" + std::to_string(_intelligence);
    _parameters.setString(_parametersString);
    int weaponDamage = Game::currentGame->GetPlayer()->GetWeapon()->CalculateDamage(_strength, _agility, _intelligence);
    int weaponDistance  = Game::currentGame->GetPlayer()->GetWeapon()->GetDistance();
    _weaponString = "Damage:" + std::to_string(weaponDamage) + " Distance:" + std::to_string(weaponDistance);
    _weapon.setString(_weaponString);
    UpdatePosition();
}

void Stats::UpdatePosition() {
    _position = Game::currentGame->GetMainWindow()->mapPixelToCoords(sf::Vector2i(210, 0), Game::currentGame->GetPlayer()->getCamera());
    _parameters.setPosition(_position);
    _weapon.setPosition(_position + sf::Vector2f(0, 10));
    _background.setPosition(_position);
}

Stats::Stats() {
    _background.setSize(sf::Vector2f(170, 25));
    _background.setFillColor(sf::Color(20, 20, 20));
    _font.loadFromFile("../resources/fonts/VT323-Regular.ttf");
    _weapon.setFillColor(sf::Color::White);
    _parameters.setFillColor(sf::Color::White);
    _weapon.setFont(_font);
    _parameters.setFont(_font);
    _strength = 0;
    _agility = 0;
    _intelligence = 0;
    _parametersString = "strength:" + std::to_string(_strength) + " agility:" + std::to_string(_agility) + " Intelligence:" + std::to_string(_intelligence);
    _parameters.setString(_parametersString);
    _parameters.setCharacterSize(22);
    _parameters.scale(0.5, 0.5);
    int weaponDamage = 0;
    int weaponDistance  = 0;
    _weaponString = "Damage:" + std::to_string(weaponDamage) + " Distance:" + std::to_string(weaponDistance);
    _weapon.setString(_weaponString);
    _weapon.setCharacterSize(22);
    _weapon.scale(0.5, 0.5);
}


