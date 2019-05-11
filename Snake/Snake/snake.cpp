#include "snake.h"
#include <cassert>

extern const float BLOCK_SIZE;
extern const sf::Vector2i WORLD_SIZES;


void Snake::Create(const sf::Vector2i& head_position)
{
    body_.clear(); 
    direction_ = None;
    Segment head = {
        head_position,
        sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)),
        sf::Color::Yellow
    };

    body_.push_back(std::move(head));
}


bool Snake::CheckSelfCollision() const
{
    for (size_t i = 1; i < body_.size(); ++i)
    {
        if (body_[i].position == body_[0].position)
        {
            return true;
        }
    }
    return false;
}


sf::Vector2i Snake::GetHeadPosition() const
{
    assert(!body_.empty());
    return body_[0].position;
}


const std::vector<Snake::Segment>& Snake::GetBody() const
{
    return body_;
}


void Snake::Render(sf::RenderWindow& window) 
{
    for (Segment&  body_part: body_)
    {
        body_part.shape.setFillColor(body_part.color);
        body_part.shape.setSize(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));
        body_part.shape.setPosition(
            sf::Vector2f(
                BLOCK_SIZE * body_part.position.x,
                BLOCK_SIZE * body_part.position.y)
        );
        window.draw(body_part.shape);
    }
}


void Snake::Update(const float dt)
{
    MoveByOneCell();
}


void Snake::MoveByOneCell()
{

    for (int i = (int)body_.size() - 1; i > 0; --i)
    {
        body_[i].position = body_[i - 1].position;
    }

    sf::Vector2i increment(0, 0);
    if (direction_ == Up)
    {
        increment.y -= 1;
    }
    if (direction_ == Down)
    {
        increment.y += 1;
    }
    if (direction_ == Left)
    {
        increment.x -= 1;
    }
    if (direction_ == Right)
    {
        increment.x += 1;
    }
    body_[0].position += increment;
}


void Snake::Grow()
{
    assert(!body_.empty());

    const size_t body_size = body_.size();

    if (body_size == 1)
    {
        Snake::Segment new_body_part;
        new_body_part.color = sf::Color::Yellow;

        sf::Vector2i increment(0, 0);
        if (direction_ == Down)
        {
            increment.y -= 1;
        }
        if (direction_ == Up)
        {
            increment.y += 1;
        }
        if (direction_ == Right)
        {
            increment.x -= 1;
        }
        if (direction_ == Left)
        {
            increment.x += 1;
        }
        new_body_part.position = sf::Vector2i(body_[0].position.x + increment.x, body_[0].position.y + increment.y);
        body_.push_back(std::move(new_body_part));
    }

    if (body_size >= 2)
    {
        Snake::Segment new_body_part;
        new_body_part.color = sf::Color::Yellow;

        const Snake::Segment& last_body_part = body_[body_size - 1];
        const Snake::Segment& penultimate_body_part = body_[body_size - 2];

        if (last_body_part.position.x == penultimate_body_part.position.x)
        {
            new_body_part.position.x = last_body_part.position.x;
            new_body_part.position.y = 2 * last_body_part.position.y - penultimate_body_part.position.y;
        }
        if (last_body_part.position.y == penultimate_body_part.position.y)
        {
            new_body_part.position.y = last_body_part.position.y;
            new_body_part.position.x = 2 * last_body_part.position.x - penultimate_body_part.position.x;
        }

        body_.push_back(std::move(new_body_part));
    }
}


Snake::Direction Snake::GetDirection() const
{
    return direction_;
}


void Snake::SetDirection(const Direction new_direction)
{
    direction_ = new_direction;
}


int Snake::GetScore() const
{
    return score_;
}


void Snake::IncreaseScore()
{
    score_ += 1;
}


int Snake::GetLives() const
{
    return lives_;
}


void Snake::DecreaseLivesByOne()
{
    if (lives_ > 0)
    {
        lives_ -= 1;
    }
}