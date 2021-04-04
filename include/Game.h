//
// Created by sevendart on 31.03.21.
//

#ifndef SIBERIANGAMEJAM_GAME_H
#define SIBERIANGAMEJAM_GAME_H

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include <random>
#include "Level.h"

class Game {
private:
    sf::RenderWindow* _mainWindow;
    sf::Clock dtClock;
    Player* player;
    Level map;
    sf::Sound sound;
    sf::SoundBuffer soundBuffer;

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
