//
// Created by sevendart on 31.03.21.
//

#include "../include/Game.h"
#include <chrono>
#include <memory>
#include <iostream>
#include "../include/Weapon.h"
#include "../include/Level.h"
#include "../include/Entry.h"

void Game::InitWindow() {
    _mainWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");
}

void Game::Init() {
    InitWindow();
    map.GenerateMap(10, 5);
    map.Load();
    map.GenerateVertices();

    Level::currentLevel = &map;

    map.AddEntry(new Entry(sf::Vector2u(1, 1), nullptr));

    auto weapon = new Weapon(Weapon::MainParameter::STRENGTH, 1,
                             std::make_shared<Modificator>(nullptr, 1), 1);
    player = new Player(1, 1, 1,
                        std::shared_ptr<Weapon>(weapon), map.GetEntries()[0]->Position);

}

Game::Game() {
    currentGame = this;
    Init();
}

void Game::Render() {
    _mainWindow->setView(player->getCamera());

    _mainWindow->clear();

    _mainWindow->draw(map);

    _mainWindow->draw(*player);

    _mainWindow->display();
}

void Game::Update() {
    UpdateSFMLEvents();
    float elapsedTime = dtClock.restart().asSeconds();
    player->UpdateSprite(elapsedTime);
}

void Game::Run() {
    while (_mainWindow->isOpen()) {
        player->Input();
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

