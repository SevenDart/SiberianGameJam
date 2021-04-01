//
// Created by sevendart on 2.04.21.
//
#ifndef SIBERIANGAMEJAM_CHARACTER_H
#define SIBERIANGAMEJAM_CHARACTER_H

#include "SFML/Graphics.hpp"
#include "Animation.h"
#include <vector>
#include <map>
#include <memory>

class Modificator;

class Character : public sf::Drawable, public sf::Transformable {
public:
    enum class States{IDLE, WALK, HIT};
    virtual void Update(float elapsedTime);
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void UpdateSprite(float elapsedTime);
    std::vector <std::shared_ptr<Modificator>> _modificators;
    std::map <States, Animation> _animations;
    States _currentState;
    sf::Sprite _sprite;
    int health;
};


#endif //SIBERIANGAMEJAM_CHARACTER_H
