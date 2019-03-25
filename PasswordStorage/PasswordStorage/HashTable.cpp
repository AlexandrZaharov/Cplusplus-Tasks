#include <cmath>
#include <iostream>
#include "HashTable.h"


HashTable::HashTable(const int bucket_size)
{
    for (int i = 0; i < bucket_size; i++)
    {
        std::vector<std::string> bucket;
        data_.push_back(bucket);
    }
}


void HashTable::Add(const std::pair<std::string, std::string>& new_pair)
{
    std::pair<std::string, std::string> new_pair_encode
        {EncodeString(new_pair.first), EncodeString(new_pair.second)};

    if (*this).Has(new_pair_encode.first) == 0)
    {
        const int key = GetHash(new_pair_encode.first);
        data_[key].push_back(new_pair_encode);
    }
}


bool HashTable::Has(const std::string& string) const
{
    for (int i = 0; i < data_[GetHash(EncodeString(string))].size(); i++)
    {
        if (DecodeString(data_[GetHash(EncodeString(string))][i].first) == string)
        {
            return true;
        } 
    }
    return false;
}


int HashTable::GetHash(const std::string& value) const
{
    return GetHashFromString(value);
}


const std::vector<std::vector<std::pair<std::string, std::string>>>& GetData() const;
{
    return data_;
}


size_t HashTable::GetBucketSize(const int bucket_index) const
{
    return data_[bucket_index].size();
}


std::string EncodeString(const std::string& string_to_encode)
{
    std::string encoded_string = string_to_encode;
    for (int i = 0; i < encoded_string.size(); i++)
    {
        encoded_string[i] += (i + 1);
    }
    return encoded_string;
}


std::string DecodeString(const std::string& string_to_decode)
{
    std::string decoded_string = string_to_decode;
    for (int i = 0; i < decoded_string.size(); i++)
    {
        decoded_string[i] -= (i + 1);
    }
    return decoded_string;
}


int GetHashFromString(const std::string& value)
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

