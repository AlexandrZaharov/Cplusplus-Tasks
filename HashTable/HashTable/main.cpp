#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "HashTable.h"


int main()
{
    int table_size = 1013;
    HashTable table_1(table_size);

    std::ifstream in_stream("cano.txt");
    for (std::string word; in_stream >> word; )
    {
        table_1.Add(word);
    }

    std::ofstream fout("hash_5.txt");
    for (int i = 0; i < table_size; i++)
    {
        fout << table_1.GetSize(i) << "\n";
    }
    return 0;
}