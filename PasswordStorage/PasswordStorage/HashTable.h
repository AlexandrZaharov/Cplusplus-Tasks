#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>


struct PasswordStorageEntry
{
    std::string nickname;
    std::string password;
};


class HashTable
{
public:

    HashTable(const int size);

    void Add(const PasswordStorageEntry& new_pair);
    bool Has(const std::string& string) const;
    int GetHash(const std::string& value) const;
    const std::vector<std::vector<PasswordStorageEntry>>& HashTable::GetData() const;

    size_t GetBucketSize(const int bucket_index) const;

private:
    std::vector<std::vector<PasswordStorageEntry>> data_;
};

std::string EncodeString(const std::string& string_to_encode);
std::string DecodeString(const std::string& string_to_decode);
int GetHashFromString(const std::string& value);

