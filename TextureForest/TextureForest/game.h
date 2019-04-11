#pragma once
#include <iostream>
#include <vector>
#include "forest.h"
#include "window.h"

class Game
{
public:
    Game();
    virtual ~Game() = default;

    void Run();
    void Update();
    void Render();
    void HandleInput();

private:
    Window main_window_;

    Forest forest_;

    sf::Texture grow_tree_;
    sf::CircleShape grow_tree_circle;

    sf::Texture burn_tree_; 
    sf::CircleShape burn_tree_circle;  

    sf::Texture dead_tree_;
    sf::CircleShape dead_tree_circle;
  
    const int image_radius_ = 30;
};
