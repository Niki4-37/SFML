#include "Splash.h"

//Private Functions

Splash::Splash(unsigned count, const float pos_x, const float pos_y) 
    : particles (count),
      vertice (sf::Points, count),
      lifetime (1.f),
      splashPosition (pos_x, pos_y),
      gravity (0.f)
{
    for (std::size_t index= 0; index < count; ++index)
    {
        float spreadAngle = (std::rand() % 180) * 3.14 / 180.f;
        float speed = (std::rand() % 20) + 1.f;
        
        this->particles[index].velocity = sf::Vector2f(std::cos(spreadAngle) * speed, std::sin(spreadAngle) * speed);
        this->particles[index].lifetime = static_cast<float>(std::rand() % 2000)/1000 + 1.f; 

        this->vertice[index].position = this->splashPosition;
    }
}

Splash::~Splash()
{

}

//Accessors

//Modifiers

//Functions

void Splash::update(const float &dt)
{
    this->gravity += 0.1f;
    for (std::size_t index= 0; index < this->particles.size(); ++index)
    {
        this->particles[index].lifetime -= dt;

        this->vertice[index].color = sf::Color(40, 150, 252, 255);
        //this->vertice[index].color.a = static_cast<sf::Uint8>(this->particles[index].lifetime * 255);
        // if (this->particles[index].lifetime <= 0.001f)
        // {
        //     this->vertice[index].color.a = 0;
        // }

        this->vertice[index].position.x += this->particles[index].velocity.x * 0.1f;
        this->vertice[index].position.y += (this->gravity - this->particles[index].velocity.y) * 0.1f;
    }
}

void Splash::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = nullptr;
    target.draw(vertice, states);
}