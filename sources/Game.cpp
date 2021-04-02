//
// Created by sevendart on 31.03.21.
//

#include "../include/Game.h"

void Game::InitWindow() {
    _mainWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");
}

void Game::Init() {
    InitWindow();
    std::vector<Cell> cells(1);
    cells[0].isReachable = false;
    cells[0].tileNumbers.push_back(337);
    cells[0].tileNumbers.push_back(32);
    map.load("../resources/mainlevbuild.png", sf::Vector2u(32, 32), cells, 1, 1);
}

Game::Game() {
    Init();
}

void Game::Render() {
    _mainWindow->clear();
    _mainWindow->draw(map);
    _mainWindow->display();
}

void Game::Update() {
    UpdateSFMLEvents();
//    float elapsedTime = dtClock.restart().asSeconds();

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

