#ifndef SPLASH_H
#define SPLASH_H

#include <iostream>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Splash : public sf::Drawable, public sf::Transformable
{
private:
    struct Particle
    {
        sf::Vector2f velocity;
        float lifetime;
    };

    std::vector<Particle> particles;
    
    sf::VertexArray vertice;
    
    float lifetime;
    sf::Vector2f splashPosition;

    float gravity;

public:    
    Splash(unsigned count, const float pos_x, const float pos_y);
    ~Splash();

    void update(const float &dt);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


#endif