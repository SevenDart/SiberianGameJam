//
// Created by sevendart on 4.04.21.
//

#include "../include/Reward.h"
#include "../include/Game.h"

Reward::Reward() {
    currentReward = this;
    _visibility = false;
    _background.setSize(sf::Vector2f(300,300));
    _position = sf::Vector2f(200, 200);
    _upgradeStrength = new Button("../resources/UI/strength_reward.png", [](int, void*)
        {
            Game::currentGame->GetPlayer()->UpgradeStrength();
            Reward::currentReward->Hide();
        }
        ,sf::Vector2f(0, 50), sf::Vector2f(50, 50));
    _upgradeAgility = new Button("../resources/UI/agility_reward.png", [](int, void*)
        {
            Game::currentGame->GetPlayer()->UpgradeAgility();
            Reward::currentReward->Hide();
        }
        ,
        sf::Vector2f(0, 50), sf::Vector2f(50,50));
    _upgradeIntelligence = new Button("../resources/UI/intelligence_reward.png", [](int, void*)
        {
            Game::currentGame->GetPlayer()->UpgradeIntelligence();
            Reward::currentReward->Hide();
        }
        , sf::Vector2f(0, 50), sf::Vector2f(50,50));
    _upgradeWeapon = new Button("../resources/UI/weapon_reward.png", [](int, void*)
        {
            Game::currentGame->GetPlayer()->UpgradeWeapon();
            Reward::currentReward->Hide();
        }
        , sf::Vector2f(0, 50), sf::Vector2f(50,50));
}

void Reward::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (_visibility) {
        target.draw(_background, states);
        target.draw(*_upgradeStrength, states);
        target.draw(*_upgradeAgility, states);
        target.draw(*_upgradeIntelligence, states);
        target.draw(*_upgradeWeapon, states);
    }
}

void Reward::Show() {
    _visibility = true;
}

void Reward::Hide() {
    _visibility = false;
}

void Reward::UpdatePosition() {
    _position = Game::currentGame->GetMainWindow()->mapPixelToCoords(sf::Vector2i(100, 100), Game::currentGame->GetPlayer()->getCamera());
    _background.setPosition(_position);
    _upgradeStrength->setPosition(_position + sf::Vector2f(50, 50));
    _upgradeAgility->setPosition(_position + sf::Vector2f(100, 50));
    _upgradeIntelligence->setPosition(_position + sf::Vector2f(150, 50));
    _upgradeWeapon->setPosition(_position + sf::Vector2f(200, 50));
}
