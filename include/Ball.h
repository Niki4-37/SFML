#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <cmath> //in this case - trigonometry
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Ball
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
    Ball(const sf::Vector2f start_position, const float speed);
    virtual ~Ball();

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