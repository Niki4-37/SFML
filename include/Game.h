#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Tile.h"
#include "Bullet.h"

class Tile;
class Bullet;

class Game
{
private:
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    sf::Texture texture;
    //GUI
    sf::Vector2f startPosition;
    sf::RectangleShape line;
    
    sf::VertexArray direction;
    sf::Vertex point;
    //Bullet
    float speed;
    std::vector<Bullet*> bullets;
    Tile *tile;

    sf::Clock dtClock;
    float dt;

    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosVeiw;

    bool mouseHeld;
    //Private functions
    void initVariables();
    void initWindow();
    void initHorizonLine();
    void initDirection();
    void initBullet();
    
    //to be continue
    void initTile();

public:
    Game();

    ~Game();

    void run();

    float getAngle(sf::Vector2f mouse_pos_veiw);

    void updatePollEvent();
    void updateMousePosition();
    void updateDirection();
    void updateTimer();
    void updateInput();
    void updateCollision();
    void updateQuantity();
    void update();

    void render();
};


#endif