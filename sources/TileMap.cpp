//
// Created by slonik on 4.1.21.
//

#include "../include/TileMap.h"

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

void TileMap::GenerateMap(int width, int heigth, int difficulty) {

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


