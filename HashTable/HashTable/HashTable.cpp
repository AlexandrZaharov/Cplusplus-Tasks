#include <cmath>
#include <iostream>
#include "HashTable.h"


HashTable::HashTable(const int basket_size)
{
    for (int i = 0; i < basket_size; i++)
    {
        std::vector<std::string> basket;
        data_.push_back(basket);
    }
}


void HashTable::Add(const std::string& new_string)
{
    if ((*this).Has(new_string) == 0)
    {
        data_[GetHash(new_string)].push_back(new_string);
    }
}


void HashTable::Remove(const std::string& string)
{
    for (int i = 0; i < data_[GetHash(string)].size(); i++)
    {
        if (data_[GetHash(string)][i] != string)
        {
            continue;
        }
        else
        {
            data_.erase(data_.begin() + i);
        }
    }
}


bool HashTable::Has(const std::string& string) const
{
    for (int i = 0; i < data_[GetHash(string)].size(); i++)
    {
        if (data_[GetHash(string)][i] == string)
        {
            return true;
        } 
    }
    return false;
}


int HashTable::GetHash(const std::string& string) const
{
    return GetHash5(string) % data_.size();
}


const auto& HashTable::GetData() const
{
    return data_;
}


size_t HashTable::GetSize(const int word_hash) const
{
    return data_[word_hash].size();
}


int HashTable::GetHash1(const std::string& value) const
{
    return 1;
}


int HashTable::GetHash2(const std::string& value) const
{
    return value[0] - 0;
}


int HashTable::GetHash3(const std::string& value) const
{
    return value.size();
}


int HashTable::GetHash4(const std::string& value) const
{
    int hash = 0;
    for (int i = 0; i < value.size(); i++)
    {
        hash += (value[i] - 0);
    }
    return hash;
}


int HashTable::GetHash5(const std::string& value) const
{
    int hash = 0;
    for (int i = 0; i < value.size(); i++)
    {
        hash += (value[i] << 2) * 179;
    }
    return hash;
}


int HashTable::GetHash6(const std::string& value) const
{
    if (value.size() == 0)
    {
        return 1;
    }

    int hash = value[0];
    for (int i = 1; i < value.size(); i++)
    {
        hash = (hash << 1) ^ value[i];
    }
    return hash;
}

