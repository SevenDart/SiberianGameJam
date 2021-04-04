//
// Created by slonik on 4/4/21.
//

#include "../include/Background.h"
#include <iostream>

bool Background::Load() {
    _tileSize = sf::Vector2u(32, 32);
    return !m_tileset.loadFromFile("../resources/outside.png");
}

bool Background::GenerateMap(int width, int heigth) {
    // Resize cells
    _cells.resize(heigth);
    for (int i = 0; i < heigth; i++) _cells[i].resize(width);
    auto IsValid = [](int x, int y, int width, int heigth) {
        return x >= 0 && x < width && y >= 0 && y < heigth;
    };
    // Fill with sand
    for (int i = 0; i < heigth; i++) {
        for (int j = 0; j < width; j++) {
            _cells[i][j] = Cell(true, nullptr, nullptr, 1, 109);
        }
    }

    int buildingsnum = 200;
    std::vector<sf::Vector2i> buildings;
    while (buildingsnum) {
        int failnum = 0;
        int threshold = 100;
        while (failnum < threshold) {
            bool fail = false;
            int x = rand() % (width - 10) + 5;
            int y = rand() % (heigth - 10) + 5;
            for (auto now : buildings) {
                if (abs(x - now.x) < 5 && abs(y - now.y) < 5) {
                    fail = true;
                    break;
                }
            }
            if (!fail) {
                switch (Random(3, 0, 10, 1, 10, 2, 10)) {
                    case 0: {
                        // AddHouse
                        AddElement(x, y, House[Random(2, 0, 1, 1, 1)]);
                        break;
                    }
                    case 1: {
                        // AddHole
                        AddElement(x, y, Cellar[Random(2, 0, 1, 1, 1)]);
                        break;
                    }
                    case 2: {
                        // AddColumn
                        AddElement(x, y, Column[Random(4, 0, 1, 1, 1, 2, 1, 3, 1)]);
                        break;
                    }
                }
                buildings.emplace_back(x, y);
                break;
            } else {
                failnum++;
            }
        }
        buildingsnum--;
    }

    // Fill with water
    for (int i = 0; i < heigth; i++) {
        for (int j = 0; j < width; j++) {
            _cells[i][j].tileNumbers.push_back(119);
        }
    }
//    return TileMap::GenerateMap(width, heigth);
}

