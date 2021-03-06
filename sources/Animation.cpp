//
// Created by sevendart on 2.04.21.
//

#include "../include/Animation.h"

bool Animation::load(std::string animFile, int count) {
    frames = new sf::Texture[count];
    this->size = count;
    for (int i = 1; i <= count; i++) {
        std::string filename = animFile + std::to_string(i) + ".png";
        if (!frames[i - 1].loadFromFile(filename)) return false;
    }
    return true;
}


sf::Texture &Animation::nextFrame(float elapsedTime) {
    currentFrame += (elapsedTime * (float)speed);
    if (currentFrame > (float)size) {
        currentFrame -= (float) size;
        isFinished = true;
    }
    return frames[(int)currentFrame % size];
}

void Animation::reset() {
    currentFrame = 0;
    isFinished = false;
}
