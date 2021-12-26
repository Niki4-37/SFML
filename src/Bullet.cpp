#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f start_position, float speed)
    : startPosition(start_position),
      speed(speed)
{
    this->timerMax = 0.01f;
    this->timer = this->timerMax;
    this->shape.setRadius(25.f);
    this->shape.setPosition(this->startPosition);
    this->shape.setFillColor(sf::Color::White);
    this->angle = 0.f;
    this->offsetX = 0.f;
    this->offsetY = 0.f;
    this->gravity = 0.f;
    this->isFired = false;
    this->boundTouched = false;
}

Bullet::~Bullet()
{

}

const sf::FloatRect Bullet::getBounds() const
{
    return this->shape.getGlobalBounds();
}

bool Bullet::atStatrPosition()
{
    return this->shape.getPosition() == this->startPosition;
}

sf::Vector2f Bullet::getPosition() const
{
    return this->shape.getPosition();
}

bool Bullet::checkFire() const
{
    return this->isFired;
}

void Bullet::setAngle(const float &angle)
{
    this->angle = angle;
}

void Bullet::makeFire()
{
    this->isFired = true;
}

void Bullet::checkWindowCollision(sf::RenderTarget *window)
{
    if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height > window->getSize().y && !this->boundTouched)
    {
        this->boundTouched = true;
        this->shape.setPosition(this->shape.getPosition().x, window->getSize().y - this->shape.getGlobalBounds().height - 1.f);
        
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
        // if (this->angle < - 3.14f / 2 && this->angle > - 3.14f)
        //     this->angle *= -1.f;
        // if (this->angle > - 3.14f / 2 && this->angle < -0.01f)
        //     this->angle *= -1.f;
    }
    //Right side collision
    if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width > window->getSize().x && !this->boundTouched)
    {
        this->boundTouched = true;
        this->shape.setPosition(window->getSize().x - this->shape.getGlobalBounds().width - 1.f, this->shape.getPosition().y);
        //this->angle -= 3.14f;
        this->angle += 3.14f;
    }
    //Left side collision 
    else if (this->shape.getGlobalBounds().left < 0.f && !this->boundTouched)
    {
        this->boundTouched = true;
        this->shape.setPosition(1.f, this->shape.getPosition().y);
        this->angle += 3.14f;
    }

    if (this->boundTouched)
    {
        this->boundTouched = false;
        // reset "gravity" value makes positive offsetY after collision 
        this->gravity = 0.f;
        this->speed *= 0.8f;
        
        std::cout << "speed: " << this->speed  << " angle: " << this->angle * 180 / 3.14 
        << " offsetX: " << this->offsetX << "\n";
    }

}

void Bullet::update(const float &dt)
{
    if (this->timer >= this->timerMax)
    {
        if (this->speed > 1.f)
        {
            this->timer = 0.f;
            // this "gravity" value makes motion ballistic-like changing offsetY in time
            this->gravity += 3.f;
            this->offsetX = this->speed * cos(this->angle) * 0.1f;
            this->offsetY = - (this->speed * sin(this->angle) - this->gravity) * 0.1f;
            this->shape.move(this->offsetX, this->offsetY);
        }
        else
        {
            this->offsetX = 0.f;
            this->offsetY = 0.f;
        }    
    }
    this->timer += dt;
}

void Bullet::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}