//
// Created by sevendart on 31.03.21.
//

#include "../include/Game.h"

void Game::InitWindow() {
    _mainWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");
}

void Game::Init() {
    InitWindow();
    CellMatrix cells(7);
    cells[0].push_back(Cell(false, NULL, NULL, 1, 75));
    for (int i = 0; i < 5; i++) {
        cells[0].push_back(Cell(false, NULL, NULL, 1, 164));
    }
    cells[0].push_back(Cell(false, NULL, NULL, 1, 64));
    for (int i = 0; i < 5; i++) {
        cells[i + 1].push_back(Cell(false, NULL, NULL, 1, 75));
        for (int j = 0; j < 5; j++) {
            cells[i + 1].push_back(Cell(true, NULL, NULL, 1, 337));
        }
        cells[i + 1].push_back(Cell(false, NULL, NULL, 1, 64));
    }
    cells[6].push_back(Cell(false, NULL, NULL, 1, 65));
    for (int i = 0; i < 5; i++) {
        cells[6].push_back(Cell(false, NULL, NULL, 1, 100));
    }
    cells[6].push_back(Cell(false, NULL, NULL, 1, 65));
    map.Load();
    map.SetCells(cells);
    map.GenerateVertices();
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

