//
// Created by slonik on 4.1.21.
//

#include "../include/TileMap.h"
#include <cstdarg>
#include <algorithm>

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}

TileMap::TileMap() {
    m_vertices.setPrimitiveType(sf::Quads);
}

TileMap::TileMap(int width, int heigth, int difficulty) {
    Load();
    GenerateMap(width, heigth, difficulty);
}

bool TileMap::Load() {
    _tileSize = sf::Vector2u(32, 32);
    return !m_tileset.loadFromFile("../resources/mainlevbuild.png");
}

TileMap::TileMap(const CellMatrix &cells) {
    Load();
    SetCells(cells);
}

void TileMap::SetCells(const CellMatrix &cells) {
    _cells = CellMatrix(cells);
}

bool TileMap::GenerateMap(int width, int heigth, int difficulty) {
    _cells.resize(heigth);
    for (int i = 0; i < heigth; i++) _cells[i].resize(width);
    for (int i = 0; i < width; i++) {
        _cells[0][i] = Cell(false, NULL, NULL, 1, 164);
        _cells[heigth - 1][i] = Cell(false, NULL, NULL, 1, 100);
    }
    for (int i = 0; i < heigth - 1; i++) {
        _cells[i][0] = Cell(false, NULL, NULL, 1, 75);
        _cells[i][width - 1] = Cell(false, NULL, NULL, 1, 64);
    }
    _cells[heigth - 1][0] = Cell(false, NULL, NULL, 1, 65);
    _cells[heigth - 1][width -  1] = Cell(false, NULL, NULL, 1, 65);
    for (int i = 1; i < heigth - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            _cells[i][j] = Cell(true, NULL, NULL, 1, 369);
        }
    }
    return true;
}

void TileMap::GenerateVertices() {
    std::vector<sf::Vertex> tmp(4);
    unsigned int heigth = _cells.size();
    if (!heigth)
        return;
    unsigned int width = _cells[0].size();
    for (unsigned int i = 0; i < heigth; i++) {
        for (unsigned int j = 0; j < width; j++) {
            const Cell *cell = &_cells[i][j];
            for (int tileNumber : cell->tileNumbers) {
                m_vertices.resize(m_vertices.getVertexCount() + 4);
                int tu = tileNumber % (m_tileset.getSize().x / _tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / _tileSize.x);
                sf::Vertex* quad = &m_vertices[m_vertices.getVertexCount() - 4];
                quad[0].position = sf::Vector2f(j * _tileSize.x, i * _tileSize.y);
                quad[1].position = sf::Vector2f((j + 1) * _tileSize.x, i * _tileSize.y);
                quad[2].position = sf::Vector2f((j + 1) * _tileSize.x, (i + 1) * _tileSize.y);
                quad[3].position = sf::Vector2f(j * _tileSize.x, (i + 1) * _tileSize.y);
                quad[0].texCoords = sf::Vector2f(tu * _tileSize.x, tv * _tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, tv * _tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, (tv + 1) * _tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * _tileSize.x, (tv + 1) * _tileSize.y);
            }
        }
    }
}

const CellMatrix &TileMap::GetCells() {
    return _cells;
}

void TileMap::AddElement(int x, int y, const TileMap::Element element) {
    for (int i = 0; i < element.height; i++) {
        for (int j = 0; j < element.width; j++) {
            _cells[y + element.offsetY + i][x + element.offsetX + j].tileNumbers.push_back(element.basetile + (i * 32) + j);
        }
    }
}

/*
 * Random choose of n pairs
 * args:
 *      n - number of pairs
 *      n pairs {int value, int chance}
 */
int TileMap::Random(int n, ...) {
    va_list list;
    va_start(list, n);
    std::vector<std::pair<int, int>> tmp;
    int value = va_arg(list, int);
    tmp.emplace_back(value, va_arg(list, int));
    for (int i = 1; i < n; i++) {
        value = va_arg(list, int);
        tmp.emplace_back(value, va_arg(list, int));
        tmp[tmp.size() - 1].second += tmp[tmp.size() - 2].second;
    }
    va_end(list);
    int res = rand() % tmp.back().second;
    return std::upper_bound(tmp.begin(), tmp.end(), std::make_pair(0, res), [](const std::pair<int, int> &left, const std::pair<int, int> &right) { return left.second < right.second;})->first;
}


