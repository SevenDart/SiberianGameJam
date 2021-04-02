//
// Created by sevendart on 2.04.21.
//

#ifndef SIBERIANGAMEJAM_USERINTERFACE_H
#define SIBERIANGAMEJAM_USERINTERFACE_H

#include "SFML/Graphics.hpp"
#include "HealthBar.h"

class UserInterface: public sf::Drawable, public sf::Transformable{
public:
    UserInterface();
    HealthBar *getHealthBar() const;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    HealthBar* _healthBar;
};


#endif //SIBERIANGAMEJAM_USERINTERFACE_H
