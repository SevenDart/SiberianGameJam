//
// Created by slonik on 4.2.21.
//

#ifndef SIBERIANGAMEJAM_ENTRY_H
#define SIBERIANGAMEJAM_ENTRY_H

#include "Level.h"

class Entry {
public:
    sf::Vector2u Position;
    std::shared_ptr<Level> NextLevel;
    std::shared_ptr<Entry> NextLevelEntry;
    Entry();
    Entry(sf::Vector2u position, std::shared_ptr<Level> nextLevel);
};

#endif //SIBERIANGAMEJAM_ENTRY_H
