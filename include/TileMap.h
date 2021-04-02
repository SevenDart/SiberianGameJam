//
// Created by slonik on 4.1.21.
//

#ifndef SIBERIANGAMEJAM_TILEMAP_H
#define SIBERIANGAMEJAM_TILEMAP_H

#include <SFML/Graphics.hpp>
#include "Cell.h"

typedef std::vector<std::vector<Cell>> CellMatrix;

class TileMap : public sf::Drawable, public sf::Transformable {
protected:
    CellMatrix _cells;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u _tileSize;
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    TileMap();
    TileMap(int width, int heigth, int difficulty = 0);
    TileMap(const CellMatrix &cells);
    bool Load();
    void SetCells(const CellMatrix &cells);
    const CellMatrix &GetCells();
    void GenerateMap(int width, int heigth, int difficulty = 0);
    void GenerateVertices();


    const sf::Vector2u TILE_SIZE = sf::Vector2u(32, 32);
};

#endif //SIBERIANGAMEJAM_TILEMAP_H
