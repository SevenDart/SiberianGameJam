//
// Created by sevendart on 4.04.21.
//

#include "../include/Button.h"
#include "../include/Game.h"

#include <utility>

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

Button::Button(const std::string &textureName, std::function<void(int, void*)> action, sf::Vector2f position,
               sf::Vector2f size)
        : _action(std::move(action)) {
    _texture.loadFromFile(textureName);
    _sprite.setTexture(_texture);
    _position = position;
    _sprite.scale(size.x / _texture.getSize().x, size.y / _texture.getSize().y);
    _size = size;
}

void Button::UpdatePosition() {
    sf::Vector2f pos = Game::currentGame->GetMainWindow()->mapPixelToCoords(sf::Vector2i(_position.x, _position.y), Game::currentGame->GetPlayer()->getCamera());
    _sprite.setPosition(pos);
    this->setPosition(pos);
}

const sf::Sprite &Button::GetSprite() const {
    return _sprite;
}

const std::function<void(int, void*)> &Button::GetAction() const {
    return _action;
}

const sf::Vector2f &Button::getSize() const {
    return _size;
}

void Button::SetPosition(const sf::Vector2i &position) {
    _position = sf::Vector2f(position);
}
