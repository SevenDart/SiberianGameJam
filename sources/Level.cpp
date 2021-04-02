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
    return false;
}

bool Level::GenerateEnemies(int enemies) {
    return false;
}

bool Level::GenerateTraps(int traps) {
    return false;
}

Level::Level(Level &other) {

}

std::vector<char> &Level::ToByteArray() {
    std::vector<char> res;
    return res;
}

bool Level::GenerateEntries(int) {
    return false;
}

const std::vector<std::shared_ptr<Entry>> &Level::GetEntries() const {
    return _entries;
}

void Level::AddEntry(Entry *entry) {
    _entries.push_back(std::shared_ptr<Entry>(entry));
}

