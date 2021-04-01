//
// Created by sevendart on 2.04.21.
//

#include "../include/Character.h"

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

void Character::Update(float elapsedTime) {
    UpdateSprite(elapsedTime);
    for (Modificator modificator : _modificators) {
        modificator.getAction()(this);
    }
}

void Character::UpdateSprite(float elapsedTime) {
    _sprite.setTexture(_animations[_currentState].nextFrame(elapsedTime));
}
