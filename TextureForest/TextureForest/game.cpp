#include <iostream>
#include "game.h"
#include "forest.h"

extern const sf::Vector2u WINDOW_SIZES(420, 420);

Game::Game()
    : main_window_("TextureForest", WINDOW_SIZES)
    , forest_(7, 7)
{
    forest_.SetValue(3, 3, 10, 1, 1);
}


void Game::HandleInput()
{
    sf::sleep(sf::seconds(0.1f));
}


void Game::Run()
{
    while (!main_window_.CheckIsDone())
    {
        Update();
        Render();
        HandleInput();
    }
}


void Game::Update()
{
    forest_.Update();
    main_window_.Update();
}


void Game::Render()
{
    main_window_.BeginDraw();
    main_window_.Draw(forest_);
    main_window_.EndDraw();
}