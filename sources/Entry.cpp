//
// Created by slonik on 4.2.21.
//

#include "../include/Entry.h"

Entry::Entry() {
}

Entry::Entry(sf::Vector2u position, std::shared_ptr<Level> nextLevel) : Position(position), NextLevel(nextLevel) {
}
