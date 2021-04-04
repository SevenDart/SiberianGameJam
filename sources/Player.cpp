//
// Created by sevendart on 2.04.21.
//

#include "../include/Player.h"
#include "../include/Game.h"
#include "../include/Entry.h"
#include <memory>


Player::~Player() {

}

void Player::UpdateSprite(float elapsedTime) {
    Character::UpdateSprite(elapsedTime);
}

void Player::Input() {
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && _isPressed[sf::Keyboard::Left]) {
        Move(_indexPosition + sf::Vector2u(-1, 0));
        _isPressed[sf::Keyboard::Left] = false;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && _isPressed[sf::Keyboard::Right]) {
        Move(_indexPosition + sf::Vector2u(1, 0));
        _isPressed[sf::Keyboard::Right] = false;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _isPressed[sf::Keyboard::Up]) {
        Move(_indexPosition + sf::Vector2u(0, -1));
        _isPressed[sf::Keyboard::Up] = false;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _isPressed[sf::Keyboard::Down]) {
        Move(_indexPosition + sf::Vector2u(0, 1));
        _isPressed[sf::Keyboard::Down] = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _isPressed[sf::Keyboard::Left] = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _isPressed[sf::Keyboard::Right] = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _isPressed[sf::Keyboard::Up] = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _isPressed[sf::Keyboard::Down] = true;
    }

    _ui->MouseInput();
}

Player::Player(int strength, int agility, int intelligence, std::shared_ptr<Weapon> weapon, sf::Vector2u startPosition)
        : Character(strength, agility, intelligence,
                    weapon,startPosition) {
    _camera = sf::View(this->getPosition(), sf::Vector2f(400,300));
    Game::currentGame->GetMainWindow()->setView(_camera);
    _ui = new UserInterface();
    _ui->getHealthBar()->setMaxHp(this->_healthPoints);
    _ui->getHealthBar()->setCurrentHp(this->_healthPoints);

    _animations[States::IDLE].load("../resources/dude/anim_idle_", 4);
    _animations[States::HIT].load("../resources/dude/anim_hit_", 1);

    _isPressed[sf::Keyboard::Down] = false;
    _isPressed[sf::Keyboard::Up] = false;
    _isPressed[sf::Keyboard::Left] = false;
    _isPressed[sf::Keyboard::Right] = false;
}

void Player::GetDamage(int damage) {
    Character::GetDamage(damage);
    _ui->getHealthBar()->setCurrentHp(this->_healthPoints);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Character::draw(target, states);
    target.draw(*_ui, states);
}

const sf::View &Player::getCamera() const {
    return _camera;
}


void Player::Move(sf::Vector2u newPosition) {
    auto entries = Level::currentLevel->GetEntries();
    for (auto entry : entries) {
        if (entry->Position == newPosition) {
            if (entry->NextLevel == nullptr) {
                entry->NextLevel = std::make_shared<Level>(rand() % 5 + 10, rand() % 5 + 10, Level::LevelType::COMBAT, rand() % 10, rand() % 10);
                entry->NextLevel->Load();
                entry->NextLevel->GenerateVertices();
                entry->NextLevelEntry = std::shared_ptr<Entry>(entry->NextLevel->GetEntries().front());
                entry->NextLevelEntry->NextLevel = std::shared_ptr<Level>(Level::currentLevel);
                entry->NextLevelEntry->NextLevelEntry = entry;
                entry->NextLevel->GetCharacters().push_back(std::shared_ptr<Character>(this));
            }
            newPosition = entry->NextLevelEntry->Position;
            if (newPosition.y == 1) newPosition.y++;
            else newPosition.y--;
            entry->NextLevel->GetCells()[newPosition.y][newPosition.x].character = std::move(Level::currentLevel->GetCells()[_indexPosition.y][_indexPosition.x].character);
            _indexPosition = newPosition;
            setPosition(_indexPosition.x * 32 + 4,_indexPosition.y * 32 - 4);
            Level::currentLevel = entry->NextLevel.get();
            _camera.setCenter(this->getPosition());
            _ui->getHealthBar()->UpdatePosition();
            Game::currentGame->UpdateCharacters();
            return;
        }
    }
    Character::Move(newPosition);
    _camera.setCenter(this->getPosition());
    _ui->Update();
    Game::currentGame->UpdateCharacters();
}

void Player::Update() {
    Character::Update();
    _ui->UpdateInfo();
}

void Player::Death() {

}
