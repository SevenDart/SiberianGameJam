//
// Created by sevendart on 31.03.21.
//

#include "../include/Game.h"
#include <chrono>

void Game::InitWindow() {
    _mainWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");
}

void Game::Init() {
    InitWindow();
}

Game::Game() {
    Init();
}

void Game::Render() {
}

void Game::Update() {
    UpdateSFMLEvents();
    float elapsedTime = dtClock.restart().asSeconds();
    player->UpdateSprite(elapsedTime);
}

void Game::Run() {
    while (_mainWindow->isOpen()) {
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

