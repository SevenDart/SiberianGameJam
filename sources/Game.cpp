//
// Created by sevendart on 31.03.21.
//

#include "../include/Game.h"
#include <chrono>
#include <memory>
#include <iostream>
#include "../include/Weapon.h"
#include "../include/Entry.h"

void Game::InitWindow() {
    _mainWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");
}

void Game::Init() {
    InitWindow();
    map.GenerateLevel(9, 9);
    map.Load();
    map.GenerateVertices();

    Level::currentLevel = &map;

//    map.AddEntry(new Entry(sf::Vector2u(1, 2), nullptr));

    auto *weapon = new Weapon(Weapon::MainParameter::STRENGTH, 1,
                             std::make_shared<Modificator>(nullptr, 1), 1);

    player = new Player(1, 1, 1,
                        std::shared_ptr<Weapon>(weapon), sf::Vector2u(2,2));

    Level::currentLevel->AddCharacter(player);
}

Game::Game() {
    currentGame = this;
    Init();
}

void Game::Render() {
    _mainWindow->setView(player->getCamera());

    _mainWindow->clear();

    _mainWindow->draw(*Level::currentLevel);

    for (auto &character : Level::currentLevel->GetCharacters()) {
        _mainWindow->draw(*character);
    }

    _mainWindow->display();
}

void Game::Update() {
    UpdateSFMLEvents();
    float elapsedTime = dtClock.restart().asSeconds();

    for (auto &character: Level::currentLevel->GetCharacters())
        character->UpdateSprite(elapsedTime);
}

void Game::Run() {
    while (_mainWindow->isOpen()) {
        player->Input();
        Update();
        Render();
    }
}

void Game::UpdateSFMLEvents() {
    sf::Event event{};
    while (_mainWindow->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _mainWindow->close();
    }
}


bool Game::CheckChance(int chance) {
    std::default_random_engine generator(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    std::uniform_int_distribution<int> distribution(1,100);
    return (distribution(generator) <= chance);
}

sf::RenderWindow *Game::getMainWindow() const {
    return _mainWindow;
}

Player *Game::GetPlayer() const {
    return player;
}

void Game::UpdateCharacters() {
    auto characters = Level::currentLevel->GetCharacters();
    for (auto &character: characters) {
        character->Update();
    }
}

