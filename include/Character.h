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
    virtual void GetDamage(int damage);

    Character(int strength, int agility, int intelligence);

private:

                        //Three main parameters for a character
    int _strength;      //affects on health points
    int _agility;       //affects on a chance to not have damage
    int _intelligence;  //affects on a critical chance

    const int HEALTH_PER_POINT = 13;

    int _healthPoints;
    int _gold;

    std::vector <std::shared_ptr<Modificator>> _modificators;
    std::map <States, Animation> _animations;
    States _currentState;
    sf::Sprite _sprite;

    virtual ~Character();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void UpdateSprite(float elapsedTime);
};


#endif //SIBERIANGAMEJAM_CHARACTER_H
