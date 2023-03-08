#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>

#include <SFML/Graphics.hpp>

struct TileMap : public sf::Drawable, public sf::Transformable {
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &m_tileset;
        target.draw(m_vertices, states);
    }

public:
    bool load(const std::string& tileSet, sf::Vector2u tileSize, std::vector <std::vector <int> >& indexMap, sf::Vector2f position) {
        m_tileset.setSmooth(true);

        if (!m_tileset.loadFromFile(tileSet)) {
            return false;
        }

        unsigned int height = indexMap.size();
        unsigned int width = indexMap[0].size();

        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);
        
        for (unsigned int i = 0; i < height; i++) {
            for (unsigned int j = 0; j < width; j++) {
                int tileNumber = indexMap[i][j];
                
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
                
                sf::Vertex* quad = &m_vertices[(i * width + j) * 4];
                
                quad[0].position = sf::Vector2f(position.x + j * tileSize.x, position.y + i * tileSize.y);
                quad[1].position = sf::Vector2f(position.x + (j + 1) * tileSize.x, position.y + i * tileSize.y);
                quad[2].position = sf::Vector2f(position.x + (j + 1) * tileSize.x, position.y + (i + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(position.x + j * tileSize.x, position.y + (i + 1) * tileSize.y);
                
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        }

        return true;
    }
};


#endif