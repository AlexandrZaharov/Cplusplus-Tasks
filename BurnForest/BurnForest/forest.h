#pragma once

#include <iostream>
#include <vector>
#include <istream>
#include <ostream>

struct Tree
{
    int health_ = 10;
    int strength_ = 5;
    size_t current_status_ = 0;
};

enum {STATUS_GROW, STATUS_BURN, STATUS_DEAD};

class Forest
{

    friend std::ostream& operator<<(std::ostream& os, const Forest& matrix);

public: 
    Forest(const size_t height, const size_t witdh);

    size_t GetHealth(const size_t height_index, const size_t width_index) const;
    size_t GetCurrentStatus(const size_t height_index, const size_t width_index) const;
    size_t GetHeight() const;
    size_t GetWidth() const;
   
    void SetValue(const size_t height_index, const size_t width_index,
                                            const int health, const int strength,  const int current_status);

    void Update();

    int GetBurnNeighbour(int y_coord, int x_coord);

private:
    std::vector<std::vector<Tree>> data_;
};

std::ostream& operator<<(std::ostream& output_stream, const Forest& matrix);

