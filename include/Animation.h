//
// Created by sevendart on 2.04.21.
//
#include "SFML/Graphics.hpp"

#ifndef SIBERIANGAMEJAM_ANIMATION_H
#define SIBERIANGAMEJAM_ANIMATION_H


class Animation {
public:
    bool load(std::string animFile, int count);
    void reset();
    sf::Texture &nextFrame(float elapsedTime);
    bool isFinished = false;
    int speed = 10;
private:
    int size = 0;
    float currentFrame = 0;
    sf::Texture *frames;
};


#endif //SIBERIANGAMEJAM_ANIMATION_H
