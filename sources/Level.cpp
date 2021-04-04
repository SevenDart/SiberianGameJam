//
// Created by slonik on 4.2.21.
//

#include "../include/Level.h"

#include <memory>
#include <queue>
#include <climits>
#include "../include/Entry.h"
#include "../include/Goblin.h"
#include "../include/Dwarf.h"

Level::Level() : TileMap() {
}

Level::Level(int width, int heigth, Level::LevelType type, int traps, int enemies) {
    Load();
    GenerateLevel(width, heigth, type, traps, enemies);
    levelType = type;
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
    GenerateTraps(width, heigth, traps);
    return true;
}

void Level::AddCharacter(Character *character) {
    sf::Vector2u startPosition = character->GetIndexPosition();
    GetCells()[startPosition.y][startPosition.x].character = std::shared_ptr<Character>(character);
    character->setPosition(startPosition.x * TILE_SIZE.x + 4,
                      startPosition.y * TILE_SIZE.y - 4);
    _characters.push_back(std::shared_ptr<Character>(character));
}

bool Level::GenerateEnemies(int width, int heigth, int enemies) {
    for (int i = 0; i < enemies; i++) {
        int threshold = 100;
        int failnum = 0;
        while (failnum < threshold) {
            bool fail = false;
            int x = rand() % (width - 2) + 1;
            int y = rand() % (heigth - 3) + 2;
            fail = _cells[y][x].character != nullptr || _cells[y][x].isTrap || !_cells[y][x].isReachable;
            if (fail) {
                failnum++;
            } else {
                switch (Random(2, 0, 1, 1, 1)) {
                    case 0: {
                        auto *goblin = new Goblin(sf::Vector2u(x, y));
                        AddCharacter(goblin);
                        break;
                    }
                    case 1: {
                        auto *dwarf = new Dwarf(sf::Vector2u(x, y));
                        AddCharacter(dwarf);
                        break;
                    }
                }
                break;
            }
        }
    }
//    _enemyCount++;
    return false;
}

bool Level::GenerateTraps(int width, int heigth, int traps) {
    for (int trap = 0; trap < traps; trap++) {
        switch (Random(2, 0, 10, 1, 90)) {
            case 0: {
                int failnum = 0;
                int threshold = 100;
                while (failnum < threshold) {
                    bool fail;
                    int x = rand() % (width - 2) + 1;
                    int y = rand() % (heigth - 3) + 2;
                    _cells[y][x].isTrap = true;
                    fail = !CheckReachability();
                    if (fail) {
                        failnum++;
                        _cells[y][x].isTrap = false;
                    } else {
                        _cells[y][x].tileNumbers.push_back(836);
                        _cells[y][x].modificator = std::make_shared<Modificator>(Modificator([](std::shared_ptr<Character> character) { character->GetDamage(INT_MAX); }, 1));
                        break;
                    }
                }
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
        } else {
            if (Random(2, 0, 1, 1, 1)) {
                AddElement(x, 1, TopRoundDoor);
            } else {
                AddElement(x, 1, TopSquareDoor);
            }
            _entries.push_back(std::make_shared<Entry>(sf::Vector2u(x, 1), nullptr));
        }
    }
    return entry.size() >= 2;
}

std::vector<std::shared_ptr<Entry>> &Level::GetEntries() {
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
    int lightoffset = 0;
    int darkoffset = 32 * 8;
    int offset = Random(2, lightoffset, 1, darkoffset, 1);
    for (int i = heigth - 1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            if (!_cells[i][j].tileNumbers.empty()) continue;
            switch (_CellTypeGrid[i][j]) {
                case CellType::FLOOR: {
                    _cells[i][j] = Cell(true, NULL, NULL, 1,
//                                        Random(29,
                                        Random(9,
                                               336 + offset, 500,
//                                               344, 1, 345, 1, 346, 1, 347, 1, 348, 1, 349, 1,
//                                               376, 1, 381, 1,
//                                               408, 1, 413, 1,
//                                               440, 1, 445, 1,
//                                               472, 1, 477, 1,
//                                               504, 1, 505, 1, 506, 1, 507, 1, 508, 1, 509, 1,
                                               537 + offset, 5, 538 + offset, 5, 539 + offset, 5, 540 + offset, 5,
                                               569 + offset, 5, 570 + offset, 5, 571 + offset, 5, 572 + offset, 5
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

bool Level::CheckReachability() {
    int height = _cells.size();
    if (!height || _entries.empty()) return false;
    int width = _cells[0].size();
    static const int dx[] = {-1, 0, 1, 0};
    static const int dy[] = {0, 1, 0, -1};
    auto IsValid = [](int x, int y, int width, int height) {
        return x >= 0 && x < width && y >= 0 && y < height;
    };
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited;
    visited.resize(height);
    for (int i = 0; i < height; i++) visited[i].resize(width);
    q.push(std::make_pair(_entries.front()->Position.x, _entries.front()->Position.y));
    while (!q.empty()) {
        std::pair<int, int> now = q.front();
        q.pop();
        visited[now.second][now.first] = true;
        for (int i = 0; i < 4; i++) {
            if (IsValid(now.first + dx[i], now.second + dy[i], width, height)) {
                int tox = now.first + dx[i], toy = now.second + dy[i];
                if (visited[toy][tox]) continue;
                if (_cells[toy][tox].isReachable && !_cells[toy][tox].isTrap) q.push(std::make_pair(now.first + dx[i], now.second + dy[i]));
            }
        }
    }
    for (auto entry : _entries) {
        int y = entry->Position.y + (entry->Position.y == 1 ? 1 : -1);
        int x = entry->Position.x;
        if (!visited[y][x]) return false;
    }
    return true;
}

std::vector<std::shared_ptr<Character>> &Level::GetCharacters() {
    return _characters;
}

std::vector<std::shared_ptr<Button>> Level::GetButtons() {
    return _buttons;
}

void Level::AddButton(Button *button) {
    _buttons.push_back(std::shared_ptr<Button>(button));
}

void Level::ClearButtons() {
    _buttons.clear();
}

void Level::AddDeadCharacter(std::shared_ptr<Character> character) {
    _deadCharacters.push_back(character);
}



