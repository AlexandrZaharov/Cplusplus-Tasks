#include "game.h"
#include <cassert>

extern const sf::Vector2u WINDOW_SIZES(800, 600);
extern const sf::Vector2i WORLD_SIZES(40, 25);
extern const float BLOCK_SIZE = 18.0f; 


Game::Game()
    : main_window_("Snake", WINDOW_SIZES),
    message_box_(
        sf::Vector2i(WORLD_SIZES.x / 5, WORLD_SIZES.y),
        sf::Vector2i(WORLD_SIZES.x / 2, WORLD_SIZES.y / 2),
        50
    )
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    world_.Create();
}


void Game::Run()
{
    const float updates_per_seconds = 10.0f;
    const sf::Time time_per_update = sf::seconds(1.0f / updates_per_seconds);

    sf::Clock clock;
    sf::Time time_sinse_last_update = sf::Time::Zero;
    while (!main_window_.CheckIsDone())
    {
        time_sinse_last_update += clock.restart();
        while (time_sinse_last_update >= time_per_update)
        {
            HandleInput();
            Update(time_per_update.asSeconds());

            time_sinse_last_update -= time_per_update;
        }

        Render();
    }
}


void Game::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
        world_.snake_.GetDirection() != Snake::Direction::Down)
    {
        world_.snake_.SetDirection(Snake::Direction::Up);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        world_.snake_.GetDirection() != Snake::Direction::Up)
    {
        world_.snake_.SetDirection(Snake::Direction::Down);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
        world_.snake_.GetDirection() != Snake::Direction::Right)
    {
        world_.snake_.SetDirection(Snake::Direction::Left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
        world_.snake_.GetDirection() != Snake::Direction::Left)
    {
        world_.snake_.SetDirection(Snake::Direction::Right);
    }
}


void Game::Update(const float dt)
{
    main_window_.Update(dt);
    if (world_.snake_.GetLives() > 0)
    {
        world_.Update(dt);
    }
    assert(world_.snake_.GetScore() >= 0);
    assert(world_.snake_.GetLives() >= 0);
    if (world_.snake_.GetLives() == 0)
    {
        message_box_.Add("Game over!");
        message_box_.Add("Your score: " + std::to_string(world_.snake_.GetScore()));
    }
    else
    {
        message_box_.Add("Current Score: " + std::to_string(world_.snake_.GetScore()));
        message_box_.Add("Current Lives: " + std::to_string(world_.snake_.GetLives()));
    }
    message_box_.Update(dt);
}


void Game::Render()
{
    main_window_.BeginDraw();

    main_window_.Draw(world_);
    main_window_.Draw(message_box_);

    main_window_.EndDraw();
}