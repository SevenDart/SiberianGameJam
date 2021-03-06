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

    struct Element {
        int basetile;
        int width, height;
        int offsetX, offsetY;
    };
    constexpr static const Element TopSquareDoor = {181, 3, 3, -1, -1};
    constexpr static const Element TopRoundDoor = {921, 3, 3, -1, -1};
    constexpr static const Element BottomDoor = {278, 3, 2, -1, -1};
    void AddElement(int x, int y, const Element element);
    static int Random(int n, ...);


    CellMatrix _cells;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u _tileSize;
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    TileMap();
    TileMap(int width, int heigth);
    TileMap(const CellMatrix &cells);
    virtual bool Load();
    void SetCells(const CellMatrix &cells);
    CellMatrix & GetCells();
    virtual bool GenerateMap(int width, int heigth);
    virtual void GenerateVertices();

    const sf::Vector2u TILE_SIZE = sf::Vector2u(32, 32);
};

#endif //SIBERIANGAMEJAM_TILEMAP_H
