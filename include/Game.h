//
// Created by sevendart on 31.03.21.
//

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "TileMap.h"

#ifndef SIBERIANGAMEJAM_GAME_H
#define SIBERIANGAMEJAM_GAME_H


class Game {
private:
    sf::RenderWindow* _mainWindow;
    TileMap map;

    void InitWindow();
    void Init();
    void Render();
    void Update();
    void UpdateSFMLEvents();
public:

    Game();
    void Run();

};


#endif //SIBERIANGAMEJAM_GAME_H
