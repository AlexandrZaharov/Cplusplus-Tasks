#include <iostream>
#include "game.h"
#include "forest.h"

extern const sf::Vector2u WINDOW_SIZES(420, 420);

Game::Game()
    : main_window_("TextureForest", WINDOW_SIZES)
    , forest_(7, 7)
{
    forest_.SetValue(3, 3, 10, 1, 1);

    grow_tree_.loadFromFile("../data/grow_tree.jpg");
    grow_tree_.setSmooth(true);
    grow_tree_circle.setTexture(&grow_tree_);
    grow_tree_circle.setRadius(image_radius_);

    burn_tree_.loadFromFile("../data/burn_tree.jpg");
    burn_tree_.setSmooth(true);
    burn_tree_circle.setTexture(&burn_tree_);
    burn_tree_circle.setRadius(image_radius_);

    dead_tree_.loadFromFile("../data/dead_tree.jpg");
    dead_tree_.setSmooth(true);
    dead_tree_circle.setTexture(&dead_tree_);
    dead_tree_circle.setRadius(image_radius_);

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
    int image_x_coord = 0;
    int image_y_coord = 0;

    main_window_.BeginDraw();
    for (size_t i = 0; i < forest_.GetHeight(); i++)
    {
        for (size_t j = 0; j < forest_.GetWidth(); j++)
        {
            if (forest_.GetData()[i][j].current_status_ == GROW_TREE)
            {
                grow_tree_circle.setPosition(sf::Vector2f(image_x_coord, image_y_coord));
                main_window_.Draw(grow_tree_circle);
            }
            if (forest_.GetData()[i][j].current_status_ == BURN_TREE)
            {
                burn_tree_circle.setPosition(sf::Vector2f(image_x_coord, image_y_coord));
                main_window_.Draw(burn_tree_circle);
            }
            if (forest_.GetData()[i][j].current_status_ == DEAD_TREE)
            {
                dead_tree_circle.setPosition(sf::Vector2f(image_x_coord, image_y_coord));
                main_window_.Draw(dead_tree_circle);
            }
            image_x_coord += 2 * image_radius_;
        }
        image_x_coord = 0;
        image_y_coord += 2 * image_radius_;
    }
    main_window_.EndDraw();
}