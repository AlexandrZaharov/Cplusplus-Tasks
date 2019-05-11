#include "apple.h"

extern const float BLOCK_SIZE;
extern const sf::Vector2i WORLD_SIZES;


void Apple::Create(const sf::Vector2i& new_position)
{
    position_ = new_position;
    shape_.setRadius(BLOCK_SIZE / 2);
}


sf::Vector2i Apple::GetPosition() const
{
    return position_;
}


void Apple::Update(const float dt)
{
}


void Apple::Render(sf::RenderWindow& window)
{
    sf::CircleShape apple = shape_; 
    apple.setFillColor(sf::Color::Red);
    apple.setPosition(sf::Vector2f(position_.x * BLOCK_SIZE, position_.y * BLOCK_SIZE));
    window.draw(apple);
}