#include "Game.h"

void Game::initVariables()
{
    this->window = nullptr;

    if (!this->texture.loadFromFile("../ResourseFiles/grass1.png"))
        std::cout << "Failed to load texture";

    this->startPosition.x = 0.f;
    this->startPosition.y = 540.f;

//    this->angle = 0.f;

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
    this->line.setFillColor(sf::Color::Red);
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

void Game::initBullet()
{
    this->bullets.push_back(new Bullet(this->startPosition, this->speed));  //, this->angle
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
    this->initBullet();
    this->initTile();

}

Game::~Game()
{
    delete this->window;
    
    for (auto &bullet : this->bullets)
        delete bullet;

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
    this->point.color = sf::Color::White;
    this->direction.append(this->point);
    this->point.position = this->mousePosVeiw;
    this->point.color = sf::Color::White;
    this->direction.append(this->point);
}

void Game::updateTimer()
{
    this->dt = this->dtClock.restart().asSeconds();
    ////Debugging/////////////////////////
    // std::cout << this->dt << "\n";   //
    //////////////////////////////////////
}

void Game::updateInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!this->mouseHeld)
        {
            this->mouseHeld = true;

            std::cout << "Game::updateInput angle: " << this->getAngle(this->mousePosVeiw) * 180 / 3.14 << "\n";    
        
            for (auto &bullet : this->bullets)
            {
                if (bullet->atStatrPosition())
                    bullet->setAngle(this->getAngle(this->mousePosVeiw));
                    bullet->makeFire();
            }
        }
    }
    else
        this->mouseHeld = false;
    
    ////Make own update function
    if (this->bullets.back()->getPosition().x >= 
        this->startPosition.x + 
        this->bullets.back()->getBounds().width ||
        this->bullets.back()->getPosition().y >= 
        this->startPosition.y + 
        this->bullets.back()->getBounds().height)
    {
        this->bullets.push_back(new Bullet(this->startPosition, this->speed));  //, this->angle
    }
}

void Game::updateCollision()
{
    for (auto &bullet : this->bullets)
        bullet->checkWindowCollision(this->window);
}

void Game::updateQuantity()
{
    if (this->bullets.size() > 11)
    {
        delete this->bullets.at(0);
        this->bullets.erase(this->bullets.begin());
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
    for (auto &bullet : this->bullets)
        if (bullet->checkFire())
            bullet->update(this->dt);
    this->updateQuantity();


}

void Game::render()
{
    this->window->clear();

    this->tile->render(this->window);

    this->window->draw(this->line);

    this->window->draw(this->direction);
    
    for (auto &bullet : this->bullets)
        bullet->render(this->window);

    this->window->display();
}