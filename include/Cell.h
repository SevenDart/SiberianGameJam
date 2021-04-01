//
// Created by slonik on 4.2.21.
//

#ifndef SIBERIANGAMEJAM_CELL_H
#define SIBERIANGAMEJAM_CELL_H

#include <vector>
#include "include/Modificator.h"

class Cell {
public:
    bool isReachable;
    Modificator modificator;
    std::vector<int> tileNumbers;
};

#endif //SIBERIANGAMEJAM_CELL_H
