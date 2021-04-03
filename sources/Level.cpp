//
// Created by slonik on 4.2.21.
//

#include "../include/Level.h"

#include <memory>
#include <queue>
#include "../include/Entry.h"
#include "../include/Goblin.h"

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
    int minNumberOfDoors = std::max(2, width / 7);
    GenerateCellTypeGrid(width, heigth);
    GenerateMap(width, heigth);
    GenerateEntries(width, heigth, Random(4,
                                          minNumberOfDoors, 50,
                                          minNumberOfDoors + 1, 20,
                                          minNumberOfDoors + 2, 5,
                                          minNumberOfDoors + 3, 1));
    GenerateEnemies(width, heigth, enemies);
    GenerateTraps(width, heigth, enemies);
    return true;
}

void Level::AddCharacter(Character *character) {
    sf::Vector2u startPosition = character->GetIndexPosition();
    GetCells()[startPosition.x][startPosition.y].character = std::shared_ptr<Character>(character);
    character->setPosition(startPosition.x * TILE_SIZE.x,
                      startPosition.y * TILE_SIZE.y);
    _characters.push_back(std::shared_ptr<Character>(character));
}

bool Level::GenerateEnemies(int width, int heigth, int enemies) {
    // TODO: Generate Enemies;
    auto *goblin = new Goblin(sf::Vector2u(5,5));
    AddCharacter(goblin);
    return false;
}

bool Level::GenerateTraps(int width, int heigth, int traps) {
    for (int trap = 0; trap < traps; trap++) {
        switch (Random(2, 0, 10, 1, 90)) {
            case 0: {
                int failnum = 0;
                int threshold = 0;
                break;
            }
            case 1: {
                break;
            }
        }
    }
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
    for (int now : entry) {
        int x = now % (width - 4) + 2;
        if (now / (width - 4)) {
            _entries.push_back(std::make_shared<Entry>(sf::Vector2u(x, heigth - 1), nullptr));
            AddElement(x, heigth - 1, BottomDoor);
//            _cells[heigth - 1][x].isReachable = true;
        } else {
            if (Random(2, 0, 1, 1, 1)) {
                AddElement(x, 1, TopRoundDoor);
            } else {
                AddElement(x, 1, TopSquareDoor);
            }
            _entries.push_back(std::make_shared<Entry>(sf::Vector2u(x, 1), nullptr));
//            _cells[1][x].isReachable = true;
        }
    }
    return entry.size() >= 2;
}

const std::vector<std::shared_ptr<Entry>> &Level::GetEntries() const {
    return _entries;
}

void Level::AddEntry(Entry *entry) {
    _entries.push_back(std::shared_ptr<Entry>(entry));
}

bool Level::GenerateMap(int width, int heigth) {
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

void Level::GenerateCellTypeGrid(int width, int heigth, int difficulty) {
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

bool Level::IsReachable(int x1, int y1, int x2, int y2) {
    int width = _cells.size();
    if (!width) return false;
    int heght = _cells[0].size();
    static int dx[] = {-1, 0, 1, 0};
    static int dy[] = {0, 1, 0, -1};
    auto IsValid = [](int x, int y, int width, int height) {
        return x >= 0 && x < width && y >= 0 && y < height;
    };
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited;
    visited.resize(heght);
    for (int i = 0; i < heght; i++) visited[i].resize(width);
    q.push(std::make_pair(x1, y1));
    while (!q.empty()) {
        std::pair<int, int> now = q.front();
        q.pop();
        visited[now.second][now.first] = true;
        for (int i = 0; i < 4; i++) {
            if (IsValid(now.first + dx[i], now.second + dy[i], width, heght)) {
                int tox = now.first + dx[i], toy = now.second + dy[i];
                if (x2 == tox && y2 == toy) return true;
                if (_cells[toy][tox].isReachable && !_cells[toy][tox].isTrap) q.push(std::make_pair(now.first + dx[i], now.second + dy[i]));
            }
        }
    }
    return false;
}

std::vector<std::shared_ptr<Character>> &Level::GetCharacters() {
    return _characters;
}


