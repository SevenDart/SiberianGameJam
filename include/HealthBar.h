//
// Created by sevendart on 2.04.21.
//

#ifndef SIBERIANGAMEJAM_HEALTHBAR_H
#define SIBERIANGAMEJAM_HEALTHBAR_H

#include "SFML/Graphics.hpp"

class HealthBar : public sf::Drawable, public sf::Transformable {
private:
    int _maxHP;
    int _currentHP;

    sf::Vector2f _position = sf::Vector2f(300,300);
    sf::Vector2f _outerSize = sf::Vector2f(100,20);
    sf::Vector2f _innerSize = _outerSize;

    sf::RectangleShape _outerRectangle;
    sf::RectangleShape _innerRectangle;
public:
    void UpdatePosition(sf::Vector2f position);
    void setCurrentHp(int currentHp);
    void setMaxHp(int maxHp);
    HealthBar(int maxHp, int currentHp);
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //SIBERIANGAMEJAM_HEALTHBAR_H
