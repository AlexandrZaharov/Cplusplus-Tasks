#pragma once
#include <vector>
#include <string>
#include <iostream>


class HashTable
{
public:

    HashTable(const int size);

    void Add(const std::string& new_string);
    void Remove(const std::string& string);
    bool Has(const std::string& string) const;
    int GetHash(const std::string& value) const;
    const auto& GetData() const;

    size_t GetSize(const int word_hash) const;

private:
    std::vector<std::vector<std::string>> data_;
};

int GetHash1(const std::string& value);
int GetHash2(const std::string& value);
int GetHash3(const std::string& value);
int GetHash4(const std::string& value);
int GetHash5(const std::string& value);
int GetHash6(const std::string& value);