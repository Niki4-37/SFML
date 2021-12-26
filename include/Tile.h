#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class Tile
{
private:
    sf::Sprite sprite;

public:
    Tile(const float pos_x, const float pos_y, sf::Texture &texture);
    ~Tile();

    void render(sf::RenderTarget *target);
};

#endif