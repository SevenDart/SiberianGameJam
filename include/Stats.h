//
// Created by sevendart on 4.04.21.
//

#ifndef SIBERIANGAMEJAM_STATS_H
#define SIBERIANGAMEJAM_STATS_H

#include "SFML/Graphics.hpp"

class Stats : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape _background;
    sf::Vector2f _position;

    int _strength;
    int _agility;
    int _intelligence;

    std::string _parametersString;
    std::string _weaponString;

    sf::Font _font;
    sf::Text _parameters;
    sf::Text _weapon;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:

    void UpdateParameters();
    void UpdatePosition();

    Stats();
};


#endif //SIBERIANGAMEJAM_STATS_H
