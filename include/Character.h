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
class Weapon;

class Character : public sf::Drawable, public sf::Transformable {
public:
    enum class States{IDLE, WALK, HIT};

    virtual void Update();
    virtual void UpdateSprite(float elapsedTime);

    virtual void GetDamage(int damage);
    virtual void Attack(Character character);
    virtual void Move(sf::Vector2u newPosition);

    void GetModificator(Modificator modificator);

    const sf::Vector2u &GetIndexPosition() const;

    Character(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon, sf::Vector2u startPosition);
    virtual ~Character();
protected:

                        //Three main parameters for a character
    int _strength;      //affects on health points
    int _agility;       //affects on a chance to not have damage
    int _intelligence;  //affects on a critical chance

    const int HEALTH_PER_POINT = 13;

    int _healthPoints;
    int _gold;

    std::shared_ptr<Weapon> _weapon;

    sf::Vector2u _indexPosition;

    std::vector <std::shared_ptr<Modificator>> _modificators;
    std::map <States, Animation> _animations;
    States _currentState;
    sf::Sprite _sprite;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //SIBERIANGAMEJAM_CHARACTER_H
