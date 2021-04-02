//
// Created by sevendart on 2.04.21.
//

#ifndef SIBERIANGAMEJAM_PLAYER_H
#define SIBERIANGAMEJAM_PLAYER_H

#include "SFML/Graphics.hpp"
#include "Character.h"
#include "UserInterface.h"

class Player : public Character {
private:
    sf::View _camera;
    ~Player() override;
    UserInterface* _ui;
public:
    Player(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon);
    void UpdateSprite(float elapsedTime) override;
    void Update() override;
    void Input();
    virtual void GetDamage(int damage) override;
    const sf::View &getCamera() const;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //SIBERIANGAMEJAM_PLAYER_H
