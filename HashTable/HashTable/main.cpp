#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "HashTable.h"

std::string TrimWord(const std::string& raw_word)
{
    size_t begin_pos = 0;
    size_t word_length = raw_word.npos;

    for (size_t i = 0; i < raw_word.size(); i++)
    {
        if (isalpha(raw_word[i]))
        {
            begin_pos = i;
            break;
        }
    }

    for (size_t i = begin_pos; i < raw_word.size(); i++)
    {
        if (!isalpha(raw_word[i]))
        {
            word_length = i - begin_pos;
            break;
        }
    }

    return raw_word.substr(begin_pos, word_length);
}

int main()
{
    int table_size = 1013;
    HashTable table_1(table_size);

    std::ifstream in_stream("cano.txt");
    for (std::string word; in_stream >> word; )
    {
        table_1.Add(TrimWord(word));
    }

    std::ofstream fout("hash_4.txt");
    for (int i = 0; i < table_size; i++)
    {
        fout << table_1.GetSize(i) << "\n";
    }
    return 0;
}