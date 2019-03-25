#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>


class HashTable
{
public:

    HashTable(const int size);

    void Add(const std::pair<std::string, std::string>& new_pair);
    bool Has(const std::string& string) const;
    int GetHash(const std::string& value) const;
    const std::vector<std::vector<std::pair<std::string, std::string>>>& GetData() const;

    size_t GetBucketSize(const int bucket_index) const;

private:
    std::vector<std::vector<std::pair<std::string, std::string>>> data_;
};

std::string EncodeString(const std::string& string_to_encode);
std::string DecodeString(const std::string& string_to_decode);
int GetHashFromString(const std::string& value);
