//
// Created by slonik on 4.2.21.
//

#ifndef SIBERIANGAMEJAM_CELL_H
#define SIBERIANGAMEJAM_CELL_H

#include <vector>
#include "Modificator.h"

class Cell {
public:
    bool isReachable;
    std::shared_ptr<Character> character;
    std::shared_ptr<Modificator> modificator;
    std::vector<int> tileNumbers;
    Cell();
    Cell(bool isReachable, std::shared_ptr<Character> character, std::shared_ptr<Modificator> modificator, int n, ...);
};

#endif //SIBERIANGAMEJAM_CELL_H
