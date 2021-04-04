//
// Created by sevendart on 4.04.21.
//

#ifndef SIBERIANGAMEJAM_REWARD_H
#define SIBERIANGAMEJAM_REWARD_H

#include "SFML/Graphics.hpp"
#include "Button.h"
#include <memory>

class Reward : public sf::Drawable, public sf::Transformable {
private:
    sf::Font font;
    sf::Text text;

    std::vector<std::shared_ptr<Button>> _buttons;

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

    bool isVisibility() const;

    const std::vector<std::shared_ptr<Button>> &getButtons() const;

    Reward();
};


#endif //SIBERIANGAMEJAM_REWARD_H
