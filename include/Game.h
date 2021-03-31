//
// Created by sevendart on 31.03.21.
//

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#ifndef SIBERIANGAMEJAM_GAME_H
#define SIBERIANGAMEJAM_GAME_H


class Game {
private:
    sf::Window* _mainWindow;

    void InitWindow();
    void Init();
    void Render();
    void Update();

public:

    Game();
    void Run();

};


#endif //SIBERIANGAMEJAM_GAME_H
