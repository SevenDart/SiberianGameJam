//
// Created by sevendart on 31.03.21.
//

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <random>

#ifndef SIBERIANGAMEJAM_GAME_H
#define SIBERIANGAMEJAM_GAME_H


class Game {
private:
    sf::Window* _mainWindow;
    sf::Clock dtClock;

    void InitWindow();
    void Init();
    void Render();
    void Update();
    void UpdateSFMLEvents();
public:
    Game();
    void Run();
    static bool CheckChance(int chance);
};


#endif //SIBERIANGAMEJAM_GAME_H
