#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <cmath> //in this case - trigonometry
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Bullet
{
private:
//Variables
sf::Vector2f startPosition;
float timerMax;
float timer;
sf::CircleShape shape;
float speed;
float angle;
float offsetX;
float offsetY;
float gravity;
bool isFired;
bool boundTouched;

//Private functions
   
public:
//Constructors and Destructors
    Bullet(const sf::Vector2f start_position, const float speed);
    virtual ~Bullet();

//Accessors
    const sf::FloatRect getBounds() const;
    bool atStatrPosition();
    sf::Vector2f getPosition() const;
    bool checkFire() const;
//Modifiers
    void setAngle(const float &angle);
    void makeFire();
//Functions
    void checkWindowCollision(sf::RenderTarget *window);
    void update(const float &dt);
    void render(sf::RenderTarget *target);
};

#endif