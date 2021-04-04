//
// Created by sevendart on 31.03.21.
//

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Player.h"
#include <random>
#include "Level.h"

#ifndef SIBERIANGAMEJAM_GAME_H
#define SIBERIANGAMEJAM_GAME_H


class Game {
private:
    sf::RenderWindow* _mainWindow;
    sf::Clock dtClock;
    Player* player;
    Level map;

    void InitWindow();
    void Init();
    void Render();
    void UpdateSFMLEvents();
public:
    inline static Game* currentGame;

    sf::RenderWindow *GetMainWindow() const;

    Player *GetPlayer() const;

    Game();
    void Run();
    void Update();
    void CheckCombatButtons();
    void UpdateCharacters();
    static bool CheckChance(int chance);
};


#endif //SIBERIANGAMEJAM_GAME_H
