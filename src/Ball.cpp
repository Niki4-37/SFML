#include "Ball.h"

Ball::Ball(const sf::Vector2f start_position, float speed)
    : startPosition(start_position),
      speed(speed)
{
    this->timerMax = 0.01f;
    this->timer = this->timerMax;
    this->shape.setRadius(25.f);
    this->shape.setPosition(this->startPosition);
    this->shape.setFillColor(sf::Color::White);
    this->shape.setOrigin(0.f, this->shape.getGlobalBounds().height / 2);
    this->angle = 0.f;
    this->velocity.x = 0.f;
    this->velocity.y = 0.f;
    this->gravity = 0.f;
    this->isFired = false;
    this->boundTouched = false;
}

Ball::~Ball()
{
    for (auto &splash : this->splashes)
        delete splash;
}

const sf::FloatRect Ball::getBounds() const
{
    return this->shape.getGlobalBounds();
}

bool Ball::atStatrPosition()
{
    return this->shape.getPosition() == this->startPosition;
}

sf::Vector2f Ball::getPosition() const
{
    return this->shape.getPosition();
}

bool Ball::checkFire() const
{
    return this->isFired;
}

void Ball::setAngle(const float &angle)
{
    this->angle = angle;
}

void Ball::makeFire()
{
    this->isFired = true;
}

void Ball::checkWindowCollision(sf::RenderTarget *window)
{
    //Bottom collision
    if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height > window->getSize().y && !this->boundTouched)
    {
        this->boundTouched = true;
        this->shape.setPosition(this->shape.getPosition().x, window->getSize().y - this->shape.getGlobalBounds().height / 2 - 1.f);
        
/*          |y           Check the angle and make positive value of sin(angle).
*       2   |   1        Makes mirror reflection relative to the x-axis
*    _______|_______     if angle lies in 3-d or 4-th quarter
*           |       x
*       3   |   4
*           | 
 */
        if (this->angle > 3.14f && this->angle < 2 * 3.14f)
            this->angle *= -1.f;

        if (this->angle > - 3.14f && this->angle < -0.01f)
            this->angle *= -1.f;

        this->splashes.push_back(new Splash(static_cast<int>(0.5f * this->speed), this->shape.getPosition().x, this->shape.getPosition().y + this->shape.getGlobalBounds().height));

    }
    //Right side collision
    if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width > window->getSize().x && !this->boundTouched)
    {
        this->boundTouched = true;
        this->shape.setPosition(window->getSize().x - this->shape.getGlobalBounds().width - 1.f, this->shape.getPosition().y);
        //rotate ball direction by 180 degrees
        this->angle += 3.14f;
        //set positive value of sin(angle) if this ball upper motion
        if (this->velocity.y < - 0.01f)
            this->angle *= -1.f;
    }
    //Left side collision 
    else if (this->shape.getGlobalBounds().left < 0.f && !this->boundTouched)
    {
        this->boundTouched = true;
        this->shape.setPosition(1.f, this->shape.getPosition().y);
        this->angle += 3.14f;
        if (this->velocity.y < - 0.01f)
            this->angle *= -1.f;
    }

    if (this->boundTouched)
    {
        this->boundTouched = false;
        // reset "gravity" value, makes positive offsetY after collision 
        this->gravity = 0.f;
        this->speed *= 0.8f;
        
        std::cout << "speed: " << this->speed  << "   angle:" << this->angle * 180 / 3.14 
        << "   offsetX: " << this->velocity.x << "   offsetY: " << this->velocity.y << "\n" ;
    }

}

void Ball::update(const float &dt)
{
    if (this->timer >= this->timerMax)
    {
        if (this->speed > 1.f)
        {
            this->timer = 0.f;
            // this "gravity" value makes ballistic-like motion changing offsetY in time
            this->gravity += 3.f;
            this->velocity = sf::Vector2f(this->speed * cos(this->angle) * 0.1f, - (this->speed * sin(this->angle) - this->gravity) * 0.1f);
            this->shape.move(this->velocity);
        }
        else
        {
            this->velocity.x = 0.f;
            this->velocity.y = 0.f;
        }    
    }
    this->timer += dt;

    for (auto &splash : this->splashes)
        splash->update(dt);

    if (this->splashes.size() > 5)
    {
        delete this->splashes.at(0);
        this->splashes.erase(this->splashes.begin());
    }
}

void Ball::render(sf::RenderTarget *target)
{
    target->draw(this->shape);

    for (auto &splash : this->splashes)
        target->draw(*splash);
}