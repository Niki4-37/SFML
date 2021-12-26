#include "Tile.h"

Tile::Tile(const float pos_x,const float pos_y, sf::Texture &texture)
{
    this->sprite.setPosition(pos_x, pos_y);
    this->sprite.setTexture(texture);
}

Tile::~Tile()
{

}

void Tile::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}
