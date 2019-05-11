#include "world.h"

extern const float BLOCK_SIZE;
extern const sf::Vector2i WORLD_SIZES;


void World::Create()
{
    Wall right_wall;
    right_wall.Create({ WORLD_SIZES.x - 1, 0 }, { WORLD_SIZES.x, WORLD_SIZES.y });
    walls_.push_back(std::move(right_wall));

    Wall left_wall;
    left_wall.Create({ 0, 0 }, { 1, WORLD_SIZES.y });
    walls_.push_back(std::move(left_wall));

    Wall upper_wall;
    upper_wall.Create({ 0, 0 }, { WORLD_SIZES.x, 1 });
    walls_.push_back(std::move(upper_wall));

    Wall bottom_wall;
    bottom_wall.Create({ 0, WORLD_SIZES.y - 1 }, { WORLD_SIZES.x, WORLD_SIZES.y });
    walls_.push_back(std::move(bottom_wall));

    apple_.Create(FindRandomFreeCell());
    snake_.Create(FindRandomFreeCell());
}


void World::Render(sf::RenderWindow& window)
{
    snake_.Render(window);
    apple_.Render(window);
    for (Wall& wall : walls_)
    {
        wall.Render(window);
    }
}


void World::HandleCollisions()
{

    if (snake_.CheckSelfCollision())
    {
        snake_.DecreaseLivesByOne();
        snake_.Create(FindRandomFreeCell());
    }

    for (const Wall& wall : walls_)
    {
        if (wall.CheckCellInWall(snake_.GetHeadPosition()))
        {
            snake_.DecreaseLivesByOne();
            snake_.Create(FindRandomFreeCell());
            break;
        }
    }

    if (snake_.GetHeadPosition() == apple_.GetPosition())
    {
        snake_.Grow();
        snake_.IncreaseScore();
        apple_.Create(FindRandomFreeCell());
    }
}


void World::Update(const float dt)
{
    snake_.Update(dt);
    apple_.Update(dt);
    for (Wall& wall : walls_)
    {
        wall.Update(dt);
    }
    HandleCollisions();
}


sf::Vector2i World::FindRandomFreeCell() const
{
    while (true)
    {
        bool is_random_cell_collided = false;
        const sf::Vector2i random_cell_position(
            std::rand() % WORLD_SIZES.x,
            std::rand() % WORLD_SIZES.y
        );

        for (const Wall& wall : walls_)
        {
            if (wall.CheckCellInWall(random_cell_position))
            {
                is_random_cell_collided = true;
                break;
            }
        }

        if (!is_random_cell_collided)
        {
            const auto& snake_body = snake_.GetBody();
            for (const auto& snake_segment : snake_body)
            {
                if (snake_segment.position == random_cell_position)
                {
                    is_random_cell_collided = true;
                    break;
                }
            }
        }

        if (!is_random_cell_collided)
        {
            if (apple_.GetPosition() == random_cell_position)
            {
                is_random_cell_collided = true;
            }
        }

        if (!is_random_cell_collided)
        {
            return random_cell_position;
        }
    }
}
