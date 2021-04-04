//
// Created by sevendart on 31.03.21.
//

#include "../include/Game.h"
#include <chrono>
#include <memory>
#include <iostream>
#include "../include/Weapon.h"
#include "../include/Entry.h"
#include "../include/Background.h"
#include "../include/Reward.h"

void Game::InitWindow() {
    _mainWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");
}

void Game::Init() {
    InitWindow();
    map.Load();
    map.GenerateLevel(9, 9);
    map.GenerateVertices();
    Level::currentLevel = &map;

    Background::currentBackground = new Background;
    Background::currentBackground->Load();
    Background::currentBackground->GenerateMap(100, 100);
    Background::currentBackground->GenerateVertices();
    Background::currentBackground->setPosition(-50 * 32, -50 * 32);

    soundBuffer.loadFromFile("../resources/Spy.wav");
    sound.setBuffer(soundBuffer);
    sound.setLoop(true);
    sound.play();

    auto *weapon = new Weapon(Weapon::MainParameter::STRENGTH, 5,
                             std::make_shared<Modificator>(nullptr, 1), 1);

    player = new Player(1, 2, 3,
                        std::shared_ptr<Weapon>(weapon), sf::Vector2u(2,2));

    player->Update();
    Level::currentLevel->AddCharacter(player);
    reward = new Reward;
    reward->Hide();
}

Game::Game() {
    currentGame = this;
    Init();
}

void Game::Render() {
    _mainWindow->setView(player->getCamera());

    _mainWindow->clear();

    _mainWindow->draw(*Background::currentBackground);

    _mainWindow->draw(*Level::currentLevel);

    for (auto &character : Level::currentLevel->GetCharacters()) {
        _mainWindow->draw(*character);
    }

    for (auto &button : Level::currentLevel->GetButtons()) {
        _mainWindow->draw(*button);
    }

    _mainWindow->draw(*reward);

    _mainWindow->display();
}

void Game::Update() {
    UpdateSFMLEvents();
    float elapsedTime = dtClock.restart().asSeconds();

    for (auto &character: Level::currentLevel->GetCharacters())
        character->UpdateSprite(elapsedTime);

    for (auto &button: Level::currentLevel->GetButtons())
        button->UpdatePosition();

    if (Reward::currentReward->isVisibility()) {
        CheckRewardsButtons();
    }
    else {
        rewardClock.restart();
    }

    if (Level::currentLevel->levelType == Level::LevelType::COMBAT)
        CheckCombatButtons();
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

sf::RenderWindow *Game::GetMainWindow() const {
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

void Game::CheckCombatButtons() {
    for (auto button: Level::currentLevel->GetButtons()) {
        sf::IntRect buttonRect = button->GetSprite().getTextureRect();
        sf::Vector2f position = button->GetSprite().getPosition();
        buttonRect.left = position.x;
        buttonRect.top = position.y;
        sf::Vector2f mousePosition = Game::currentGame->GetMainWindow()->mapPixelToCoords(sf::Mouse::getPosition(Game::currentGame->GetMainWindow()[0]));
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//            sf::Vector2i mousePosition = sf::Mouse::getPosition();
//            std::cout << position.x << " " << position.y << "\n";
//            std::cout << buttonRect.width << " " << buttonRect.height << "\n";
//            std::cout << mousePosition.x << " " << mousePosition.y << "\n";
//            std::cout.flush();
//        }
        if (buttonRect.contains(sf::Vector2i(mousePosition.x, mousePosition.y))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2u indexPosition((position.x + 1) / 32, (position.y + 1) / 32);
                void* pointerToCharacter =(void*)Level::currentLevel->GetCells()[indexPosition.y][indexPosition.x].character.get();
                button->GetAction()(1, pointerToCharacter);
                break;
            }
        }
    }
}



void Game::CheckRewardsButtons() {
    rewardTime -= rewardClock.restart().asSeconds();
    if (rewardTime > 0) return;
    for (auto button: Reward::currentReward->getButtons()) {
        sf::IntRect buttonRect = button->GetSprite().getTextureRect();
        sf::Vector2f position = button->GetSprite().getPosition();
        buttonRect.width = 50;
        buttonRect.height = 50;
        buttonRect.left = position.x;
        buttonRect.top = position.y;
        sf::Vector2f mousePosition = Game::currentGame->GetMainWindow()->mapPixelToCoords(sf::Mouse::getPosition(Game::currentGame->GetMainWindow()[0]));
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//            sf::Vector2i mousePosition = sf::Mouse::getPosition();
//            std::cout << position.x << " " << position.y << "\n";
//            std::cout << buttonRect.width << " " << buttonRect.height << "\n";
//            std::cout << mousePosition.x << " " << mousePosition.y << "\n";
//            std::cout.flush();
//        }
        if (buttonRect.contains(sf::Vector2i(mousePosition.x, mousePosition.y))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                rewardTime = 2;
                button->GetAction()(0, nullptr);
                break;
            }
        }
    }
}
