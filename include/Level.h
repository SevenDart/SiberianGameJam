//
// Created by slonik on 4.2.21.
//

#ifndef SIBERIANGAMEJAM_LEVEL_H
#define SIBERIANGAMEJAM_LEVEL_H

#include "Character.h"
#include "TileMap.h"
#include <vector>

class Entry;

class Level : public TileMap {
protected:

    std::vector<std::shared_ptr<Character>> _characters;
    std::vector<std::shared_ptr<Entry>> _entries;

public:
    enum class LevelType {
        COMBAT,
        REST,
        TRADE
    };

    ///static link to current level
    inline static Level* currentLevel;

    ///Constructors
    Level();
    Level(int width, int heigth, LevelType type = Level::LevelType::COMBAT, int traps = 0, int enemies = 0);
    Level(CellMatrix &cells);
    Level(std::vector<char> &byteArray);
    Level(Level &other);

    std::vector<char> &ToByteArray();
    void FromByteArray(std::vector<char> &byteArray);

    const std::vector<std::shared_ptr<Entry>> &GetEntries() const;
    void AddEntry(Entry *entry);

    ///Generate functions
    bool GenerateLevel(int width, int heigth, LevelType type = Level::LevelType::COMBAT, int traps = 0, int enemies = 0);
    bool GenerateEnemies(int enemies);
    bool GenerateTraps(int traps);
    bool GenerateEntries(int entries);
};

#endif //SIBERIANGAMEJAM_LEVEL_H
