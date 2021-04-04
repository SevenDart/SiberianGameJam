//
// Created by sevendart on 2.04.21.
//

#include "../include/UserInterface.h"
#include "../include/Level.h"
#include "../include/Button.h"
#include "../include/Game.h"
#include "../include/Weapon.h"
#include <iostream>

void UserInterface::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*_healthBar, states);
    target.draw(*_attackButton, states);
}

UserInterface::UserInterface() {
    _healthBar = new HealthBar(5,5);
    std::function<void(int, void*)> _attackFunc = [](int, void*) {
        Level::currentLevel->GetButtons().clear();
        MarkEnemies();
    };
    _attackButton = new Button("../resources/UI/attack_button.png", _attackFunc, sf::Vector2f(0, 50), sf::Vector2f(50,50));
}

HealthBar *UserInterface::getHealthBar() const {
    return _healthBar;
}

void UserInterface::Update() {
    _healthBar->UpdatePosition();
    _attackButton->UpdatePosition();
}

void UserInterface::MouseInput() {
    std::vector<Button> buttons;
    buttons.push_back(*_attackButton);
    for (const auto& button: buttons) {
        sf::IntRect buttonRect = button.GetSprite().getTextureRect();
        sf::Vector2f position = button.GetSprite().getPosition();
        buttonRect.width = button.getSize().x;
        buttonRect.height = button.getSize().y;
        buttonRect.left = position.x;
        buttonRect.top = position.y;
        sf::Vector2f mousePosition = Game::currentGame->GetMainWindow()->mapPixelToCoords(sf::Mouse::getPosition(Game::currentGame->GetMainWindow()[0]));
        /*if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            std::cout << "-----------------------------------\n";
            std::cout << "Button position " << position.x << " " << position.y << "\n";
            std::cout << "button size " << buttonRect.width << " " << buttonRect.height << "\n";
            std::cout << "MOUSE " << mousePosition.x << " " << mousePosition.y << "\n";
            std::cout.flush();
        }*/
        if (buttonRect.contains(sf::Vector2i(mousePosition.x, mousePosition.y))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                button.GetAction()(0, nullptr);
        }
    }
}

void UserInterface::MarkEnemies() {
    Player* player = Game::currentGame->GetPlayer();
    CellMatrix map = Level::currentLevel->GetCells();
    sf::Vector2u playerPosition = player->GetIndexPosition();
    for (int dist = 1; dist <= player->GetWeapon()->GetDistance(); dist++) {
            int dx[] = {-dist, 0, dist, 0, -(dist - 1), -(dist - 1), (dist - 1), (dist - 1)};
            int dy[] = {0, -dist, 0, dist, -(dist - 1), (dist - 1), -(dist - 1), (dist - 1)};
            for (int i = 0; i < 8; i++) {
                if (playerPosition.y + dy[i] > map[0].size() || playerPosition.x + dx[i] > map.size()) continue;
                if (map[playerPosition.y + dy[i]][playerPosition.x + dx[i]].character != nullptr &&
                    map[playerPosition.y + dy[i]][playerPosition.x + dx[i]].character.get() != player) {

                    sf::Vector2u pos(playerPosition.y + dy[i], playerPosition.x + dx[i]);

                    sf::Vector2f buttonPosition(pos.y * Level::currentLevel->TILE_SIZE.x,
                                                pos.x * Level::currentLevel->TILE_SIZE.y);

                    sf::Vector2i buttonCoords = Game::currentGame->GetMainWindow()->mapCoordsToPixel(buttonPosition);

                    std::function<void(int, void*)> function = [](int c_args, void* args) {
                        auto character = (Character*)args;
                        Game::currentGame->GetPlayer()->Attack(character);
                        Level::currentLevel->ClearButtons();
                    };
                    auto *button = new Button("../resources/UI/marked_position.png",function,
                                              sf::Vector2f(buttonCoords),sf::Vector2f(32,32));
                    Level::currentLevel->AddButton(button);
                }
            }
    }
}


