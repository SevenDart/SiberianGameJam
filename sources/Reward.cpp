//
// Created by sevendart on 4.04.21.
//

#include "../include/Reward.h"
#include "../include/Game.h"

Reward::Reward() {
    font.loadFromFile("../resources/fonts/VT323-Regular.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString("REWARD");
    text.setCharacterSize(64);
    text.scale(0.5, 0.5);

    currentReward = this;
    _visibility = false;
    _background.setSize(sf::Vector2f(300,150));
    _background.setFillColor(sf::Color(78, 32, 4));
    _position = sf::Vector2f(100, 200);
    _upgradeStrength = new Button("../resources/UI/strength_reward.png", [](int, void*)
        {
            Game::currentGame->GetPlayer()->UpgradeStrength();
            Reward::currentReward->Hide();
        }
        ,sf::Vector2f(_position.x, _position.y), sf::Vector2f(50, 50));
    _upgradeAgility = new Button("../resources/UI/agility_reward.png", [](int, void*)
        {
            Game::currentGame->GetPlayer()->UpgradeAgility();
            Reward::currentReward->Hide();
        }
        ,
        sf::Vector2f(_position.x + 150, _position.y), sf::Vector2f(50,50));
    _upgradeIntelligence = new Button("../resources/UI/intelligence_reward.png", [](int, void*)
        {
            Game::currentGame->GetPlayer()->UpgradeIntelligence();
            Reward::currentReward->Hide();
        }
        , sf::Vector2f(_position.x + 350, _position.y), sf::Vector2f(50,50));
    _upgradeWeapon = new Button("../resources/UI/weapon_reward.png", [](int, void*)
        {
            Game::currentGame->GetPlayer()->UpgradeWeapon();
            Reward::currentReward->Hide();
        }
        , sf::Vector2f(_position.x + 500, _position.y), sf::Vector2f(50,50));

    _buttons.push_back(std::shared_ptr<Button>(_upgradeStrength));
    _buttons.push_back(std::shared_ptr<Button>(_upgradeAgility));
    _buttons.push_back(std::shared_ptr<Button>(_upgradeIntelligence));
    _buttons.push_back(std::shared_ptr<Button>(_upgradeWeapon));

}

void Reward::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (_visibility) {
        target.draw(_background, states);
        target.draw(*_upgradeStrength, states);
        target.draw(*_upgradeAgility, states);
        target.draw(*_upgradeIntelligence, states);
        target.draw(*_upgradeWeapon, states);
        target.draw(text, states);
    }
}

void Reward::Show() {
    UpdatePosition();
    _visibility = true;
}

void Reward::Hide() {
    _visibility = false;
}

void Reward::UpdatePosition() {
    _position = Game::currentGame->GetMainWindow()->mapPixelToCoords(sf::Vector2i(100, 100), Game::currentGame->GetPlayer()->getCamera());
    _background.setPosition(_position);
    text.setPosition(_position + sf::Vector2f(100, 10));
    _upgradeStrength->UpdatePosition();
    _upgradeAgility->UpdatePosition();
    _upgradeIntelligence->UpdatePosition();
    _upgradeWeapon->UpdatePosition();
}

bool Reward::isVisibility() const {
    return _visibility;
}

const std::vector<std::shared_ptr<Button>> &Reward::getButtons() const {
    return _buttons;
}


