//
// Created by sevendart on 2.04.21.
//

#ifndef SIBERIANGAMEJAM_PLAYER_H
#define SIBERIANGAMEJAM_PLAYER_H

#include "SFML/Graphics.hpp"
#include "Character.h"
#include "UserInterface.h"
#include <map>

class Player : public Character {
private:
    sf::View _camera;
    UserInterface* _ui;

    std::map<sf::Keyboard::Key, bool> _isPressed;
public:
    Player(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon, sf::Vector2u startPosition);
    ~Player() override;

    void UpdateSprite(float elapsedTime) override;
    void Update() override;
    virtual void GetDamage(int damage) override;

    void Move(sf::Vector2u newPosition) override;

    void Input();

    const sf::View &getCamera() const;


protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //SIBERIANGAMEJAM_PLAYER_H
