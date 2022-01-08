#include "Game.h"

void Game::initVariables()
{
    this->window = nullptr;

    if (!this->texture.loadFromFile("../ResourseFiles/grass1.png"))
        std::cout << "Failed to load texture";

    this->startPosition.x = 0.f;
    this->startPosition.y = 540.f;

    this->speed = 400.f;

    this->mouseHeld = false;
}

void Game::initWindow()
{
    this->videoMode.height = 1080;
    this->videoMode.width = 1920;
    this->window = new sf::RenderWindow(this->videoMode, "SFML_project", sf::Style::Default);
}

void Game::initHorizonLine()
{
    this->line.setPosition(this->startPosition);
    this->line.setSize(sf::Vector2f(this->window->getSize().x, 1.f));
    this->line.setFillColor(sf::Color::White);
}

void Game::initDirection()
{
    this->direction.setPrimitiveType(sf::Lines);
    this->point.position = this->startPosition;
    this->point.color = sf::Color::White;
    this->direction.append(this->point);
    this->point.position = this->mousePosVeiw;
    this->point.color = sf::Color::White;
    this->direction.append(this->point);
}

void Game::initBall()
{
    this->balls.push_back(new Ball(this->startPosition, this->speed));
}

//it should be a vector
void Game::initTile()
{
    this->tile = new Tile(
        static_cast<float>(this->window->getSize().x) / 2 - 50.f,
        static_cast<float>(this->window->getSize().y) - 100.f,
        this->texture
    );
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initHorizonLine();
    this->initDirection();
    this->initBall();
    this->initTile();
}

Game::~Game()
{
    delete this->window;
    
    for (auto &ball : this->balls)
        delete ball;

    delete this->tile;
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();

        this->render();
    }
}

float Game::getAngle(sf::Vector2f mouse_pos_veiw)
{
    return atan((this->startPosition.y - mouse_pos_veiw.y) / mouse_pos_veiw.x);
}

void Game::updatePollEvent()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
            this->window->close();

        if ((this->event.type == sf::Event::KeyPressed) && (this->event.key.code == sf::Keyboard::Escape))
            this->window->close(); 
    }
}

void Game::updateMousePosition()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosVeiw = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateDirection()
{
    this->direction.clear();
    this->point.position = this->startPosition;
    this->point.color = sf::Color::Red;
    this->direction.append(this->point);
    this->point.position = this->mousePosVeiw;
    this->point.color = sf::Color::Green;
    this->direction.append(this->point);
}

void Game::updateTimer()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!this->mouseHeld)
        {
            this->mouseHeld = true;

            std::cout << "Game::updateInput angle: " << this->getAngle(this->mousePosVeiw) * 180 / 3.14 << "\n";    
        
            for (auto &ball : this->balls)
            {
                if (ball->atStatrPosition())
                    ball->setAngle(this->getAngle(this->mousePosVeiw));
                    ball->makeFire();
            }
        }
    }
    else
        this->mouseHeld = false;
}

void Game::updateCollision()
{
    for (auto &ball : this->balls)
        ball->checkWindowCollision(this->window);
}

void Game::updateQuantity()
{
    //checking start position
    if (this->balls.back()->getPosition().x >= 
        this->startPosition.x + 
        this->balls.back()->getBounds().width ||
        this->balls.back()->getPosition().y >= 
        this->startPosition.y + 
        this->balls.back()->getBounds().height)
    {
        //add new ball if it's empty 
        this->balls.push_back(new Ball(this->startPosition, this->speed));
    }
    //check quantity
    if (this->balls.size() > 11)
    {
        delete this->balls.at(0);
        this->balls.erase(this->balls.begin());
    }
}

void Game::update()
{
    this->updatePollEvent();
    this->updateMousePosition();
    this->updateDirection();
    this->updateTimer();
    this->updateInput();
    this->updateCollision();
    for (auto &ball : this->balls)
        if (ball->checkFire())
            ball->update(this->dt);
    this->updateQuantity();
}

void Game::render()
{
    this->window->clear();

    this->tile->render(this->window);

    this->window->draw(this->line);

    this->window->draw(this->direction);
    
    for (auto &ball : this->balls)
        ball->render(this->window);

    this->window->display();
}