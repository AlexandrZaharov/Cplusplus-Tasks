#pragma once

#include <iostream>
#include <vector>
#include <istream>
#include <ostream>
#include "window.h"

class Forest
{

    friend std::ostream& operator<<(std::ostream& os, const Forest& matrix);

public:

    enum { GROW_TREE, BURN_TREE, DEAD_TREE };

    Forest(const size_t height, const size_t witdh);

    size_t GetHealth(const size_t height_index, const size_t width_index) const;
    size_t GetCurrentStatus(const size_t height_index, const size_t width_index) const;
    size_t GetHeight() const;
    size_t GetWidth() const;

    //const std::vector<std::vector<Tree>>& GetData() const;

    void SetValue(const size_t height_index, const size_t width_index,
        const int health, const int strength, const int current_status);

    void Update();
    
    void Render();

    int GetBurnNeighbour(int y_coord, int x_coord);

private:


    struct Tree
    {
        int health_ = 10;
        int strength_ = 5;
        size_t current_status_ = 0;
    };

    std::vector<std::vector<Tree>> data_;

    sf::Texture grow_tree_;
    sf::CircleShape grow_tree_circle;

    sf::Texture burn_tree_;
    sf::CircleShape burn_tree_circle;

    sf::Texture dead_tree_;
    sf::CircleShape dead_tree_circle;

    const int image_radius_ = 30;
};

std::ostream& operator<<(std::ostream& output_stream, const Forest& matrix);

