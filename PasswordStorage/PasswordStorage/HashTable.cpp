#include <cmath>
#include <iostream>
#include "HashTable.h"


HashTable::HashTable(const int size)
{
    for (int i = 0; i < size; i++)
    {
        std::vector<PasswordStorageEntry> bucket;
        data_.push_back(bucket);
    }
}


void HashTable::Add(const PasswordStorageEntry& new_pair)
{
    PasswordStorageEntry encode_new_pair;
    encode_new_pair.nickname = EncodeString(new_pair.nickname);
    encode_new_pair.password = EncodeString(new_pair.password);

    if ((*this).Has(encode_new_pair.nickname) == 0)
    {
        data_[GetHash(encode_new_pair.nickname)].push_back(encode_new_pair);
    }
}


bool HashTable::Has(const std::string& string) const
{
    for (size_t i = 0; i < data_[GetHash(EncodeString(string))].size(); i++)
    {
        if (string == DecodeString(data_[GetHash(EncodeString(string))][i].nickname))
        {
            return true;
        }
    }
    return false;
}


int HashTable::GetHash(const std::string& value) const
{
    return GetHashFromString(value) % data_.size();
}


const std::vector<std::vector<PasswordStorageEntry>>& HashTable::GetData() const
{
    return data_;
}


size_t HashTable::GetBucketSize(const int bucket) const
{
    return data_[bucket].size();
}













