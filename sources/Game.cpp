//
// Created by sevendart on 31.03.21.
//

#include "../include/Game.h"

void Game::InitWindow() {
    _mainWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");
}

void Game::Init() {
    InitWindow();
}

Game::Game() {
    Init();
}



void Game::Run() {
    while (_mainWindow->isOpen()) {
        Update();
        Render();
    }
}

void Game::Render() {

}

void Game::Update() {

}
