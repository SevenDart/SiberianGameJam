//
// Created by sevendart on 4.04.21.
//

#ifndef SIBERIANGAMEJAM_BUTTON_H
#define SIBERIANGAMEJAM_BUTTON_H

#include "SFML/Graphics.hpp"
#include <functional>

class Button: public sf::Drawable, public sf::Transformable {
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    std::function<void(int c_args, void*)> _action;
    sf::Vector2f _position;
    sf::Vector2f _size;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    void UpdatePosition();

    const sf::Sprite &GetSprite() const;

    const std::function<void(int, void*)> &GetAction() const;

    const sf::Vector2f &getSize() const;

    Button(const std::string &textureName, std::function<void(int, void*)> action, sf::Vector2f position,
           sf::Vector2f size);
};


#endif //SIBERIANGAMEJAM_BUTTON_H
