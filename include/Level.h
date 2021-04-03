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
private:
    enum class CellType {
        FLOOR,
        WALL
    };
    std::vector<std::vector<CellType>> _CellTypeGrid;
    void GenerateCellTypeGrid(int width, int heigth, int difficulty = 0);
    bool GenerateMap(int width, int heigth) override;
    bool GenerateEnemies(int width, int heigth, int enemies);
    bool GenerateTraps(int width, int heigth, int traps);
    bool GenerateEntries(int width, int heigth, int entries);
    bool CheckReachability();
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

    std::vector<std::shared_ptr<Entry>> &GetEntries();
    void AddEntry(Entry *entry);
    void AddCharacter(Character* character);

    std::vector<std::shared_ptr<Character>> &GetCharacters();

    ///Generate functions
    bool GenerateLevel(int width, int heigth, LevelType type = Level::LevelType::COMBAT, int traps = 0, int enemies = 0);
};

#endif //SIBERIANGAMEJAM_LEVEL_H
