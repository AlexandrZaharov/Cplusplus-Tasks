#include "forest.h"

Forest::Forest(const size_t height, const size_t width)
{
    for (size_t i = 0; i < height; i++)
    {
        std::vector<Tree> line;
        for (size_t j = 0; j < width; j++)
        {
            Tree tree;
            line.push_back(std::move(tree));
        }
        data_.push_back(std::move(line));
    }
}


size_t Forest::GetHealth(const size_t height_index, const size_t width_index) const
{
    return data_[height_index][width_index].health_;
}


size_t Forest::GetCurrentStatus(const size_t height_index, const size_t width_index) const
{
    return data_[height_index][width_index].current_status_;
}


size_t Forest::GetHeight() const
{
    return data_.size();
}


size_t Forest::GetWidth() const
{
    if (data_.size() > 0)
    {
        return data_[0].size();
    }
    return 0;
}


const std::vector<std::vector<Tree>>& Forest::GetData() const
{
    return data_;
}


void Forest::SetValue(const size_t height_index, const size_t width_index,
    const int health, const int strength, const int current_status)
{
    data_[height_index][width_index].health_ = health;
    data_[height_index][width_index].strength_ = strength;
    data_[height_index][width_index].current_status_ = current_status;
}


void Forest::Update()
{
    for (int y = 0; y < data_.size(); y++)
    {
        for (int x = 0; x < data_[0].size(); x++)
        {
            int burn_neighbours_count = GetBurnNeighbour(y, x);
            if (data_[y][x].current_status_ == GROW_TREE)
            {
                if (data_[y][x].strength_ - burn_neighbours_count >= 0)
                {
                    data_[y][x].strength_ -= burn_neighbours_count;
                }
                else
                {
                    data_[y][x].strength_ = 0;
                }
            }

            if (data_[y][x].current_status_ == BURN_TREE)
            {
                if (data_[y][x].health_ - burn_neighbours_count >= 0)
                {
                    data_[y][x].health_ -= burn_neighbours_count;
                }
                else
                {
                    data_[y][x].health_ = 0;
                }
            }
        }
    }

    for (int y = 0; y < data_.size(); y++)
    {
        for (int x = 0; x < data_[0].size(); x++)
        {
            if (data_[y][x].current_status_ == DEAD_TREE)
            {
                data_[y][x].current_status_ = GROW_TREE;
                data_[y][x].strength_ = 5;
                data_[y][x].health_ = 10;
            }
            if (data_[y][x].strength_ == 0 && data_[y][x].health_ != 0)
            {
                data_[y][x].current_status_ = BURN_TREE;
            }
            if (data_[y][x].health_ == 0)
            {
                data_[y][x].current_status_ = DEAD_TREE;
            }
        }
    }
}


int Forest::GetBurnNeighbour(int y, int x)
{
    int burn_neighbours_count = 0;
    for (int j = y - 1; j <= y + 1; j++)
    {
        for (int i = x - 1; i <= x + 1; i++)
        {
            if (j < 0 || j >= data_.size() || i < 0
                || i >= data_[0].size() || i == x && j == y)
            {
                continue;
            }
            else
            {
                if (data_[j][i].current_status_ == BURN_TREE)
                {
                    burn_neighbours_count++;
                }
            }
        }
    }
    return burn_neighbours_count;
}


std::ostream& operator<<(std::ostream& output_stream, const Forest& matrix)
{
    for (size_t y = 0; y < matrix.GetHeight(); y++)
    {
        for (size_t x = 0; x < matrix.GetWidth(); x++)
        {
            if (matrix.GetCurrentStatus(y, x) == GROW_TREE)
            {
                output_stream << '|' << " ";
            }
            if (matrix.GetCurrentStatus(y, x) == BURN_TREE)
            {
                output_stream << '*' << " ";
            }
            if (matrix.GetCurrentStatus(y, x) == DEAD_TREE)
            {
                output_stream << ' ' << " ";
            }
        }
        output_stream << "\n";
    }
    return output_stream;
}




