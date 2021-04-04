//
// Created by sevendart on 4.04.21.
//

#ifndef SIBERIANGAMEJAM_REWARD_H
#define SIBERIANGAMEJAM_REWARD_H

#include "SFML/Graphics.hpp"
#include "Button.h"

class Reward : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape _background;
    Button* _upgradeStrength;
    Button* _upgradeAgility;
    Button* _upgradeIntelligence;
    Button* _upgradeWeapon;

    sf::Vector2f _position;
    bool _visibility;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    void Show();
    void Hide();

    void UpdatePosition();

    inline static Reward* currentReward;

    Reward();
};


#endif //SIBERIANGAMEJAM_REWARD_H
