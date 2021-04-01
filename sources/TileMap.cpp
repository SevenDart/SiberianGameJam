//
// Created by slonik on 4.1.21.
//

#include "../include/TileMap.h"

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}

bool TileMap::load(const std::string &tileset, sf::Vector2u tileSize, const int *tiles, unsigned int width,
                   unsigned int heigth) {
    if (!m_tileset.loadFromFile(tileset))
        return false;
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * heigth * 4);
    for (unsigned int i = 0; i < heigth; i++) {
        for (unsigned int j = 0; j < width; j++) {
            int tileNumber = tiles[i * width + j];
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
            sf::Vertex* quad = &m_vertices[(i * width + j) * 4];
            quad[0].position = sf::Vector2f(j * tileSize.x, i * tileSize.y);
            quad[1].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
            quad[2].position = sf::Vector2f((j + 1) * tileSize.x, (i + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    return true;
}