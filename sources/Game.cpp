//
// Created by sevendart on 31.03.21.
//

#include "../include/Game.h"
#include <chrono>
#include <memory>
#include "../include/Weapon.h"

void Game::InitWindow() {
    _mainWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");
}

void Game::Init() {
    InitWindow();
    std::vector<std::vector<Cell>> cells(7);
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
    map.load("../resources/mainlevbuild.png", sf::Vector2u(32, 32), cells);


    auto weapon = new Weapon(Weapon::MainParameter::STRENGTH, 1, std::make_shared<Modificator>(nullptr, 1), 1);
    player = new Player(1, 1, 1, std::shared_ptr<Weapon>(weapon));
}

Game::Game() {
    currentGame = this;
    Init();
}

void Game::Render() {
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

