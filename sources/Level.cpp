//
// Created by slonik on 4.2.21.
//

#include "../include/Level.h"
#include "../include/Entry.h"

Level::Level() : TileMap() {
}

Level::Level(int width, int heigth, Level::LevelType type, int traps, int enemies) {
    Load();
    GenerateLevel(width, heigth, type, traps, enemies);
}

Level::Level(std::vector<char> &byteArray) {
    FromByteArray(byteArray);
}

Level::Level(CellMatrix &cells) {

}

void Level::FromByteArray(std::vector<char> &byteArray) {

}

bool Level::GenerateLevel(int width, int heigth, Level::LevelType type, int traps, int enemies) {
    GenerateCellTypeGrid(width, heigth);
    GenerateMap(width, heigth);
    GenerateEntries(width, heigth, 2);
//    GenerateEnemies();
//    GenerateTraps();
    return true;
}

bool Level::GenerateEnemies(int enemies) {
    // TODO: Generate Enemies;
    return false;
}

bool Level::GenerateTraps(int traps) {
    // TODO: Generate Traps or not to generate)))
    return false;
}

Level::Level(Level &other) {

}

std::vector<char> &Level::ToByteArray() {
    std::vector<char> res;
    return res;
}

bool Level::GenerateEntries(int width, int heigth, int entries) {
    int numCells = (width - 4) * 2;
    int failnum = 0;
    const int threshold = 100;
    std::vector<int> entry;
    while (entries > 0 && failnum < threshold) {
        bool fail = false;
        int now = rand() % numCells;
        for (int tmp : entry) {
            if ((tmp / (width - 4)) ^ (now / (width - 4))) continue;
            if (abs(tmp - now) < 3) {
                fail = true;
                break;
            }
        }
        if (!fail) {
            entries--;
            entry.push_back(now);
        } else {
            failnum += fail;
        }
    }
    for (int i = 0; i < (int) entry.size(); i++) {
        if (entry[i] / (width - 4)) {
            AddElement(entry[i] % (width - 4) + 2, heigth - 1, BottomDoor);
        } else {
            if (Random(2, 0, 1, 1, 1)) {
                AddElement(entry[i] % (width - 4) + 2, 1, TopRoundDoor);
            } else {
                AddElement(entry[i] % (width - 4) + 2, 1, TopSquareDoor);
            }
        }
    }
    return false;
}

const std::vector<std::shared_ptr<Entry>> &Level::GetEntries() const {
    return _entries;
}

void Level::AddEntry(Entry *entry) {
    _entries.push_back(std::shared_ptr<Entry>(entry));
}

bool Level::GenerateMap(int width, int heigth, int difficulty) {
    // Resize cells
    _cells.resize(heigth);
    for (int i = 0; i < heigth; i++) _cells[i].resize(width);
    auto IsValid = [](int x, int y, int width, int heigth) {
        return x >= 0 && x < width && y >= 0 && y < heigth;
    };
    for (int i = heigth - 1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            if (!_cells[i][j].tileNumbers.empty()) continue;
            switch (_CellTypeGrid[i][j]) {
                case CellType::FLOOR: {
                    _cells[i][j] = Cell(true, NULL, NULL, 1,
//                                        Random(29,
                                        Random(9,
                                               336, 500,
//                                               344, 1, 345, 1, 346, 1, 347, 1, 348, 1, 349, 1,
//                                               376, 1, 381, 1,
//                                               408, 1, 413, 1,
//                                               440, 1, 445, 1,
//                                               472, 1, 477, 1,
//                                               504, 1, 505, 1, 506, 1, 507, 1, 508, 1, 509, 1,
                                               537, 5, 538, 5, 539, 5, 540, 5,
                                               569, 5, 570, 5, 571, 5, 572, 5
                                               ));
                    break;
                }
                case CellType::WALL: {
                    if (IsValid(j, i + 1, width, heigth) && _CellTypeGrid[i + 1][j] == CellType::FLOOR) {
                        struct TopWall {
                            int tiledepend, tile;
                        };
                        TopWall walls[4] = {
                                {132, 164},
                                {133, 165},
                                {134, 166},
                                {135, 167}
                        };
                        int current = Random(4, 0, 1, 1, 1, 2, 1, 3, 1);
                        _cells[i][j] = Cell(false, NULL, NULL, 1, walls[current].tile);
                        _cells[i - 1][j] = Cell(false, NULL, NULL, 1, walls[current].tiledepend);
                    } else if (IsValid(j + 1, i, width, heigth) && _CellTypeGrid[i][j + 1] == CellType::FLOOR) { // LEFT
                        _cells[i][j] = Cell(false, NULL, NULL, 1, 194);
                    } else if (IsValid(j - 1, i, width, heigth) && _CellTypeGrid[i][j - 1] == CellType::FLOOR) { // RIGHT
                        _cells[i][j] = Cell(false, NULL, NULL, 1, 193);
                    } else if (IsValid(j, i - 1, width, heigth) && _CellTypeGrid[i - 1][j] == CellType::FLOOR) { // DOWN
                        _cells[i][j] = Cell(false, NULL, NULL, 1, Random(4, 100, 1, 101, 1, 102, 1, 103, 1));
                    } else if (IsValid(j, i - 1, width, heigth) && _CellTypeGrid[i - 1][j] == CellType::WALL // down left corner
                            && IsValid(j + 1, i, width, heigth) && _CellTypeGrid[i][j + 1] == CellType::WALL
                            && IsValid(j + 1, i - 1, width, heigth) && _CellTypeGrid[i - 1][j + 1] == CellType::FLOOR) {
                        _cells[i][j] = Cell(false, NULL, NULL, 1, 66);
                    } else if (IsValid(j, i - 1, width, heigth) && _CellTypeGrid[i - 1][j] == CellType::WALL // down right corner
                              && IsValid(j - 1, i, width, heigth) && _CellTypeGrid[i][j - 1] == CellType::WALL
                              && IsValid(j - 1, i - 1, width, heigth) && _CellTypeGrid[i - 1][j - 1] == CellType::FLOOR) {
                        _cells[i][j] = Cell(false, NULL, NULL, 1, 73);
                    } else if (IsValid(j, i + 1, width, heigth) && _CellTypeGrid[i + 1][j] == CellType::WALL // up left corner
                              && IsValid(j + 1, i, width, heigth) && _CellTypeGrid[i][j + 1] == CellType::WALL
                              && IsValid(j + 1, i + 1, width, heigth) && _CellTypeGrid[i + 1][j + 1] == CellType::FLOOR) {
                        _cells[i][j] = Cell(false, NULL, NULL, 1, 194);
                        _cells[i - 1][j] = Cell(false, NULL, NULL, 1, 162);
                    } else if (IsValid(j, i + 1, width, heigth) && _CellTypeGrid[i + 1][j] == CellType::WALL // up right corner
                              && IsValid(j - 1, i, width, heigth) && _CellTypeGrid[i][j - 1] == CellType::WALL
                              && IsValid(j - 1, i + 1, width, heigth) && _CellTypeGrid[i + 1][j - 1] == CellType::FLOOR) {
                        _cells[i][j] = Cell(false, NULL, NULL, 1, 193);
                        _cells[i - 1][j] = Cell(false, NULL, NULL, 1, 161);
                    }
                }
            }
        }
    }
}

void Level::GenerateCellTypeGrid(int width, int heigth) {
    // Resize grid
    _CellTypeGrid.resize(heigth);
    for (int i = 0; i < heigth; i++) {
        _CellTypeGrid[i].resize(width);
    }
    // Fill walls
    for (int i = 0; i < width; i++) {
        _CellTypeGrid[0][i] = CellType::WALL;
        _CellTypeGrid[1][i] = CellType::WALL;
        _CellTypeGrid[heigth - 1][i] = CellType::WALL;
    }
    for (int i = 0; i < heigth; i++) {
        _CellTypeGrid[i][0] = CellType::WALL;
        _CellTypeGrid[i][width - 1] = CellType::WALL;
    }
    // Fill floor
    for (int i = 2; i < heigth - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            _CellTypeGrid[i][j] = CellType::FLOOR;
        }
    }
}
