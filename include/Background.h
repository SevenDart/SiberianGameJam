//
// Created by slonik on 4/4/21.
//

#ifndef SIBERIANGAMEJAM_BACKGROUND_H
#define SIBERIANGAMEJAM_BACKGROUND_H

#include "TileMap.h"

class Background : public TileMap {
protected:
    constexpr static const Element House[] = {
            {0, 5, 5, -2, -2},
            {5, 5, 5, -2, -2}
    };
    constexpr static const Element Cellar[] = {
            {50, 2, 3, 0, -1},
            {52, 2, 3, -1, -1}
    };
    constexpr static const Element Column[] = {
            {80, 3, 3, -1, -2},
            {83, 3  , 3, -1, -2},
            {86, 1, 3, 0, -2},
            {87, 1, 3, 0, -2}
    };

public:
    bool Load() override;
    bool GenerateMap(int width, int heigth) override;
    inline static Background* currentBackground;
};

#endif //SIBERIANGAMEJAM_BACKGROUND_H
