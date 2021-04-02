//
// Created by sevendart on 31.03.21.
//

#include "../include/Game.h"

void Game::InitWindow() {
    _mainWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");
}

void Game::Init() {
    InitWindow();
    std::vector<Cell> cells;
    cells.push_back(Cell(false, NULL, 1, 75));
    for (int i = 0; i < 5; i++) {
        cells.push_back(Cell(false, NULL, 1, 164));
    }
    cells.push_back(Cell(false, NULL, 1, 64));
    for (int i = 0; i < 5; i++) {
        cells.push_back(Cell(false, NULL, 1, 75));
        for (int j = 0; j < 5; j++) {
            cells.push_back(Cell(true, NULL, 1, 337));
        }
        cells.push_back(Cell(false, NULL, 1, 64));
    }
    cells.push_back(Cell(false, NULL, 1, 65));
    for (int i = 0; i < 5; i++) {
        cells.push_back(Cell(false, NULL, 1, 100));
    }
    cells.push_back(Cell(false, NULL, 1, 65));
    map.load("../resources/mainlevbuild.png", sf::Vector2u(32, 32), cells, 7, 7);
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

