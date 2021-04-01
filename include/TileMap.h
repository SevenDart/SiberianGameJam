//
// Created by slonik on 4.1.21.
//

#ifndef SIBERIANGAMEJAM_TILEMAP_H
#define SIBERIANGAMEJAM_TILEMAP_H

#include <SFML/Graphics.hpp>
#include "Cell.h"

class TileMap : public sf::Drawable, public sf::Transformable {
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<Cell> &cells, unsigned int width, unsigned int heigth);
};



#endif //SIBERIANGAMEJAM_TILEMAP_H
