//
// Created by slonik on 4/2/21.
//

#include "../include/Cell.h"
#include <cstdarg>

Cell::Cell() {
    isReachable = false;
    tileNumbers.clear();
    modificator.reset();
}

Cell::Cell(bool isReachable, std::shared_ptr<Character> character, std::shared_ptr<Modificator> modificator, int n,
           ...) : isReachable(isReachable), character(character), modificator(modificator) {
    va_list list;
    va_start(list, n);
    for (int i = 0; i < n; i++) {
        tileNumbers.push_back(va_arg(list, int));
    }
    va_end(list);
}


