//
// Created by sevendart on 2.04.21.
//

#ifndef SIBERIANGAMEJAM_USERINTERFACE_H
#define SIBERIANGAMEJAM_USERINTERFACE_H

#include "SFML/Graphics.hpp"
#include "HealthBar.h"
#include "Button.h"
#include "Stats.h"

class UserInterface: public sf::Drawable, public sf::Transformable{
public:
    UserInterface();

    HealthBar *getHealthBar() const;
    Stats* GetStats() const;
    void Update();
    void MouseInput();
    void UpdateInfo();

    static void MarkEnemies();

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    HealthBar* _healthBar;
    Stats* _stats;
    Button* _attackButton;
};


#endif //SIBERIANGAMEJAM_USERINTERFACE_H
